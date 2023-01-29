#ifndef HEADER_CURL_IMPERSONATE_H
#define HEADER_CURL_IMPERSONATE_H

#define IMPERSONATE_MAX_HEADERS 32

/*
 * curl-impersonate: Options to be set for each supported target browser.
 */
struct impersonate_opts {
  const char *target;
  int httpversion;
  int ssl_version;
  const char *ciphers;
  /* Elliptic curves (TLS extension 10).
   * Passed to CURLOPT_SSL_EC_CURVES */
  const char *curves;
  /* Signature hash algorithms (TLS extension 13).
   * Passed to CURLOPT_SSL_SIG_HASH_ALGS */
  const char *sig_hash_algs;
  /* Enable TLS NPN extension. */
  bool npn;
  /* Enable TLS ALPN extension. */
  bool alpn;
  /* Enable TLS ALPS extension. */
  bool alps;
  /* Enable TLS session ticket extension. */
  bool tls_session_ticket;
  /* TLS certificate compression algorithms.
   * (TLS extension 27) */
  const char *cert_compression;
  const char *http_headers[IMPERSONATE_MAX_HEADERS];
  const char *http2_pseudo_headers_order;
  bool http2_no_server_push;
  bool tls_permute_extensions;
  /* Other TLS options will come here in the future once they are
   * configurable through curl_easy_setopt() */
};

/*
 * curl-impersonate: Global array of supported browsers and their
 * impersonation options.
 */
extern const struct impersonate_opts impersonations[];

#endif /* HEADER_CURL_IMPERSONATE_H */
