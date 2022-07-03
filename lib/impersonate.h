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
  const char *http_headers[IMPERSONATE_MAX_HEADERS];
  /* Other TLS options will come here in the future once they are
   * configurable through curl_easy_setopt() */
};

/*
 * curl-impersonate: Global array of supported browsers and their
 * impersonation options.
 */
extern const struct impersonate_opts impersonations[];

#endif /* HEADER_CURL_IMPERSONATE_H */
