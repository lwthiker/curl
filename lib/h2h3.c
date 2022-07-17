/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2022, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/

#include "curl_setup.h"
#include "urldata.h"
#include "h2h3.h"
#include "transfer.h"
#include "sendf.h"
#include "strcase.h"

/* The last 3 #include files should be in this order */
#include "curl_printf.h"
#include "curl_memory.h"
#include "memdebug.h"

/*
 * Curl_pseudo_headers() creates the array with pseudo headers to be
 * used in a HTTP/2 or HTTP/3 request.
 */

#if defined(USE_NGHTTP2) || defined(ENABLE_QUIC)

/* USHRT_MAX is 65535 == 0xffff */
#define HEADER_OVERFLOW(x) \
  (x.namelen > 0xffff || x.valuelen > 0xffff - x.namelen)

/*
 * Check header memory for the token "trailers".
 * Parse the tokens as separated by comma and surrounded by whitespace.
 * Returns TRUE if found or FALSE if not.
 */
static bool contains_trailers(const char *p, size_t len)
{
  const char *end = p + len;
  for(;;) {
    for(; p != end && (*p == ' ' || *p == '\t'); ++p)
      ;
    if(p == end || (size_t)(end - p) < sizeof("trailers") - 1)
      return FALSE;
    if(strncasecompare("trailers", p, sizeof("trailers") - 1)) {
      p += sizeof("trailers") - 1;
      for(; p != end && (*p == ' ' || *p == '\t'); ++p)
        ;
      if(p == end || *p == ',')
        return TRUE;
    }
    /* skip to next token */
    for(; p != end && *p != ','; ++p)
      ;
    if(p == end)
      return FALSE;
    ++p;
  }
}

typedef enum {
  /* Send header to server */
  HEADERINST_FORWARD,
  /* Don't send header to server */
  HEADERINST_IGNORE,
  /* Discard header, and replace it with "te: trailers" */
  HEADERINST_TE_TRAILERS
} header_instruction;

/* Decides how to treat given header field. */
static header_instruction inspect_header(const char *name, size_t namelen,
                                         const char *value, size_t valuelen) {
  switch(namelen) {
  case 2:
    if(!strncasecompare("te", name, namelen))
      return HEADERINST_FORWARD;

    return contains_trailers(value, valuelen) ?
           HEADERINST_TE_TRAILERS : HEADERINST_IGNORE;
  case 7:
    return strncasecompare("upgrade", name, namelen) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  case 10:
    return (strncasecompare("connection", name, namelen) ||
            strncasecompare("keep-alive", name, namelen)) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  case 16:
    return strncasecompare("proxy-connection", name, namelen) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  case 17:
    return strncasecompare("transfer-encoding", name, namelen) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  default:
    return HEADERINST_FORWARD;
  }
}

/*
 * curl-impersonate:
 * Determine the position of HTTP/2 pseudo headers.
 * The pseudo headers ":method", ":path", ":scheme", ":authority"
 * are sent in different order by different browsers. An important part of the
 * impersonation is ordering them like the browser does.
 */
static int http2_pseudo_header_index(struct Curl_easy *data,
                                     const char *header,
                                     size_t *index)
{
  char *off;
  // Use the Chrome ordering by default:
  // :method, :authority, :scheme, :path
  char *order = "masp";
  if(data->set.str[STRING_HTTP2_PSEUDO_HEADERS_ORDER])
    order = data->set.str[STRING_HTTP2_PSEUDO_HEADERS_ORDER];

  if(strlen(order) != 4)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  // :method should always be first
  if(order[0] != 'm')
    return CURLE_BAD_FUNCTION_ARGUMENT;

  // All pseudo-headers must be present
  if(!strchr(order, 'm') ||
     !strchr(order, 'a') ||
     !strchr(order, 's') ||
     !strchr(order, 'p'))
    return CURLE_BAD_FUNCTION_ARGUMENT;

  if(strcasecompare(header, ":method"))
    off = strchr(order, 'm');
  else if(strcasecompare(header, ":authority"))
    off = strchr(order, 'a');
  else if(strcasecompare(header, ":scheme"))
    off = strchr(order, 's');
  else if(strcasecompare(header, ":path"))
    off = strchr(order, 'p');
  else
    return CURLE_BAD_FUNCTION_ARGUMENT;

  *index = off - order;
  return CURLE_OK;
}

CURLcode Curl_pseudo_headers(struct Curl_easy *data,
                             const char *mem, /* the request */
                             const size_t len /* size of request */,
                             struct h2h3req **hp)
{
  struct connectdata *conn = data->conn;
  size_t nheader = 0;
  size_t i;
  size_t header_idx;
  size_t authority_idx;
  char *hdbuf = (char *)mem;
  char *end, *line_end;
  struct h2h3pseudo *nva = NULL;
  struct h2h3req *hreq = NULL;
  char *vptr;

  /* Calculate number of headers contained in [mem, mem + len). Assumes a
     correctly generated HTTP header field block. */
  for(i = 1; i < len; ++i) {
    if(hdbuf[i] == '\n' && hdbuf[i - 1] == '\r') {
      ++nheader;
      ++i;
    }
  }
  if(nheader < 2) {
    goto fail;
  }
  /* We counted additional 2 \r\n in the first and last line. We need 3
     new headers: :method, :path and :scheme. Therefore we need one
     more space. */
  nheader += 1;
  hreq = malloc(sizeof(struct h2h3req) +
                sizeof(struct h2h3pseudo) * (nheader - 1));
  if(!hreq) {
    goto fail;
  }

  nva = &hreq->header[0];

  /* Extract :method, :path from request line
     We do line endings with CRLF so checking for CR is enough */
  line_end = memchr(hdbuf, '\r', len);
  if(!line_end) {
    goto fail;
  }

  /* Method does not contain spaces */
  end = memchr(hdbuf, ' ', line_end - hdbuf);
  if(!end || end == hdbuf)
    goto fail;
  /* curl-impersonate: Set the index of ":method" based on libcurl option */
  if(http2_pseudo_header_index(data, ":authority", &authority_idx))
    goto fail;
  if(http2_pseudo_header_index(data, ":method", &header_idx))
    goto fail;
  /* This is needed to overcome the fact that curl will only move the authority
   * header into its place after all other headers have been placed. */
  if(header_idx > authority_idx)
    header_idx--;
  nva[header_idx].name = H2H3_PSEUDO_METHOD;
  nva[header_idx].namelen = sizeof(H2H3_PSEUDO_METHOD) - 1;
  nva[header_idx].value = hdbuf;
  nva[header_idx].valuelen = (size_t)(end - hdbuf);

  hdbuf = end + 1;

  /* Path may contain spaces so scan backwards */
  end = NULL;
  for(i = (size_t)(line_end - hdbuf); i; --i) {
    if(hdbuf[i - 1] == ' ') {
      end = &hdbuf[i - 1];
      break;
    }
  }
  if(!end || end == hdbuf)
    goto fail;
  /* curl-impersonate: Set the index of ":path" based on libcurl option */
  if(http2_pseudo_header_index(data, ":path", &header_idx))
    goto fail;
  if(header_idx > authority_idx)
    header_idx--;
  nva[header_idx].name = H2H3_PSEUDO_PATH;
  nva[header_idx].namelen = sizeof(H2H3_PSEUDO_PATH) - 1;
  nva[header_idx].value = hdbuf;
  nva[header_idx].valuelen = (end - hdbuf);

  /* curl-impersonate: Set the index of ":scheme" based on libcurl option */
  if(http2_pseudo_header_index(data, ":scheme", &header_idx))
    goto fail;
  if(header_idx > authority_idx)
    header_idx--;
  nva[header_idx].name = H2H3_PSEUDO_SCHEME;
  nva[header_idx].namelen = sizeof(H2H3_PSEUDO_SCHEME) - 1;
  vptr = Curl_checkheaders(data, STRCONST(H2H3_PSEUDO_SCHEME));
  if(vptr) {
    vptr += sizeof(H2H3_PSEUDO_SCHEME);
    while(*vptr && ISSPACE(*vptr))
      vptr++;
    nva[header_idx].value = vptr;
    infof(data, "set pseudo header %s to %s", H2H3_PSEUDO_SCHEME, vptr);
  }
  else {
    if(conn->handler->flags & PROTOPT_SSL)
      nva[header_idx].value = "https";
    else
      nva[header_idx].value = "http";
  }
  nva[header_idx].valuelen = strlen((char *)nva[header_idx].value);

  authority_idx = 0;
  i = 3;
  while(i < nheader) {
    size_t hlen;

    hdbuf = line_end + 2;

    /* check for next CR, but only within the piece of data left in the given
       buffer */
    line_end = memchr(hdbuf, '\r', len - (hdbuf - (char *)mem));
    if(!line_end || (line_end == hdbuf))
      goto fail;

    /* header continuation lines are not supported */
    if(*hdbuf == ' ' || *hdbuf == '\t')
      goto fail;

    for(end = hdbuf; end < line_end && *end != ':'; ++end)
      ;
    if(end == hdbuf || end == line_end)
      goto fail;
    hlen = end - hdbuf;

    if(hlen == 4 && strncasecompare("host", hdbuf, 4)) {
      authority_idx = i;
      nva[i].name = H2H3_PSEUDO_AUTHORITY;
      nva[i].namelen = sizeof(H2H3_PSEUDO_AUTHORITY) - 1;
    }
    else {
      nva[i].namelen = (size_t)(end - hdbuf);
      /* Lower case the header name for HTTP/3 */
      Curl_strntolower((char *)hdbuf, hdbuf, nva[i].namelen);
      nva[i].name = hdbuf;
    }
    hdbuf = end + 1;
    while(*hdbuf == ' ' || *hdbuf == '\t')
      ++hdbuf;
    end = line_end;

    switch(inspect_header((const char *)nva[i].name, nva[i].namelen, hdbuf,
                          end - hdbuf)) {
    case HEADERINST_IGNORE:
      /* skip header fields prohibited by HTTP/2 specification. */
      --nheader;
      continue;
    case HEADERINST_TE_TRAILERS:
      nva[i].value = "trailers";
      nva[i].valuelen = sizeof("trailers") - 1;
      break;
    default:
      nva[i].value = hdbuf;
      nva[i].valuelen = (end - hdbuf);
    }

    nva[i].value = hdbuf;
    nva[i].valuelen = (end - hdbuf);

    ++i;
  }

  /* curl-impersonate: Set the index of ":authority" based on libcurl option */
  if(http2_pseudo_header_index(data, ":authority", &header_idx))
    goto fail;
  /* :authority must come before non-pseudo header fields */
  if(authority_idx && authority_idx != header_idx) {
    struct h2h3pseudo authority = nva[authority_idx];
    for(i = authority_idx; i > header_idx; --i) {
      nva[i] = nva[i - 1];
    }
    nva[i] = authority;
  }

  /* Warn stream may be rejected if cumulative length of headers is too
     large. */
#define MAX_ACC 60000  /* <64KB to account for some overhead */
  {
    size_t acc = 0;

    for(i = 0; i < nheader; ++i) {
      acc += nva[i].namelen + nva[i].valuelen;

      infof(data, "h2h3 [%.*s: %.*s]",
            (int)nva[i].namelen, nva[i].name,
            (int)nva[i].valuelen, nva[i].value);
    }

    if(acc > MAX_ACC) {
      infof(data, "http_request: Warning: The cumulative length of all "
            "headers exceeds %d bytes and that could cause the "
            "stream to be rejected.", MAX_ACC);
    }
  }

  hreq->entries = nheader;
  *hp = hreq;

  return CURLE_OK;

  fail:
  free(hreq);
  return CURLE_OUT_OF_MEMORY;
}

void Curl_pseudo_free(struct h2h3req *hp)
{
  free(hp);
}

#endif /* USE_NGHTTP2 or HTTP/3 enabled */
