#include "curl_setup.h"

#include "impersonate.h"

const struct impersonate_opts impersonations[] = {
  {
    .target = "ff91esr",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "aes_128_gcm_sha_256,"
      "chacha20_poly1305_sha_256,"
      "aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_128_gcm_sha_256,"
      "ecdhe_rsa_aes_128_gcm_sha_256,"
      "ecdhe_ecdsa_chacha20_poly1305_sha_256,"
      "ecdhe_rsa_chacha20_poly1305_sha_256,"
      "ecdhe_ecdsa_aes_256_gcm_sha_384,"
      "ecdhe_rsa_aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_256_sha,"
      "ecdhe_ecdsa_aes_128_sha,"
      "ecdhe_rsa_aes_128_sha,"
      "ecdhe_rsa_aes_256_sha,"
      "rsa_aes_128_gcm_sha_256,"
      "rsa_aes_256_gcm_sha_384,"
      "rsa_aes_128_sha,"
      "rsa_aes_256_sha,"
      "rsa_3des_ede_cbc_sha",
    .http_headers = {
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:91.0) Gecko/20100101 Firefox/91.0",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
      "Accept-Language: en-US,en;q=0.5",
      "Accept-Encoding: gzip, deflate, br",
      "Upgrade-Insecure-Requests: 1",
      "Sec-Fetch-Dest: document",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-User: ?1",
      "TE: Trailers"
    }
  },
  {
    .target = "ff95",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "aes_128_gcm_sha_256,"
      "chacha20_poly1305_sha_256,"
      "aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_128_gcm_sha_256,"
      "ecdhe_rsa_aes_128_gcm_sha_256,"
      "ecdhe_ecdsa_chacha20_poly1305_sha_256,"
      "ecdhe_rsa_chacha20_poly1305_sha_256,"
      "ecdhe_ecdsa_aes_256_gcm_sha_384,"
      "ecdhe_rsa_aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_256_sha,"
      "ecdhe_ecdsa_aes_128_sha,"
      "ecdhe_rsa_aes_128_sha,"
      "ecdhe_rsa_aes_256_sha,"
      "rsa_aes_128_gcm_sha_256,"
      "rsa_aes_256_gcm_sha_384,"
      "rsa_aes_128_sha,"
      "rsa_aes_256_sha",
    .http_headers = {
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:95.0) Gecko/20100101 Firefox/95.0",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
      "Accept-Language: en-US,en;q=0.5",
      "Accept-Encoding: gzip, deflate, br",
      "Upgrade-Insecure-Requests: 1",
      "Sec-Fetch-Dest: document",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-User: ?1",
      "TE: Trailers"
    }
  },
  {
    .target = "ff98",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "aes_128_gcm_sha_256,"
      "chacha20_poly1305_sha_256,"
      "aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_128_gcm_sha_256,"
      "ecdhe_rsa_aes_128_gcm_sha_256,"
      "ecdhe_ecdsa_chacha20_poly1305_sha_256,"
      "ecdhe_rsa_chacha20_poly1305_sha_256,"
      "ecdhe_ecdsa_aes_256_gcm_sha_384,"
      "ecdhe_rsa_aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_256_sha,"
      "ecdhe_ecdsa_aes_128_sha,"
      "ecdhe_rsa_aes_128_sha,"
      "ecdhe_rsa_aes_256_sha,"
      "rsa_aes_128_gcm_sha_256,"
      "rsa_aes_256_gcm_sha_384,"
      "rsa_aes_128_sha,"
      "rsa_aes_256_sha",
    .http_headers = {
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
      "Accept-Language: en-US,en;q=0.5",
      "Accept-Encoding: gzip, deflate, br",
      "Upgrade-Insecure-Requests: 1",
      "Sec-Fetch-Dest: document",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-User: ?1",
      "TE: Trailers"
    }
  },
  {
    .target = "ff100",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "aes_128_gcm_sha_256,"
      "chacha20_poly1305_sha_256,"
      "aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_128_gcm_sha_256,"
      "ecdhe_rsa_aes_128_gcm_sha_256,"
      "ecdhe_ecdsa_chacha20_poly1305_sha_256,"
      "ecdhe_rsa_chacha20_poly1305_sha_256,"
      "ecdhe_ecdsa_aes_256_gcm_sha_384,"
      "ecdhe_rsa_aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_256_sha,"
      "ecdhe_ecdsa_aes_128_sha,"
      "ecdhe_rsa_aes_128_sha,"
      "ecdhe_rsa_aes_256_sha,"
      "rsa_aes_128_gcm_sha_256,"
      "rsa_aes_256_gcm_sha_384,"
      "rsa_aes_128_sha,"
      "rsa_aes_256_sha",
    .http_headers = {
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
      "Accept-Language: en-US,en;q=0.5",
      "Accept-Encoding: gzip, deflate, br",
      "Upgrade-Insecure-Requests: 1",
      "Sec-Fetch-Dest: document",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-User: ?1",
      "TE: Trailers"
    }
  },
  {
    .target = "ff102",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "aes_128_gcm_sha_256,"
      "chacha20_poly1305_sha_256,"
      "aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_128_gcm_sha_256,"
      "ecdhe_rsa_aes_128_gcm_sha_256,"
      "ecdhe_ecdsa_chacha20_poly1305_sha_256,"
      "ecdhe_rsa_chacha20_poly1305_sha_256,"
      "ecdhe_ecdsa_aes_256_gcm_sha_384,"
      "ecdhe_rsa_aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_256_sha,"
      "ecdhe_ecdsa_aes_128_sha,"
      "ecdhe_rsa_aes_128_sha,"
      "ecdhe_rsa_aes_256_sha,"
      "rsa_aes_128_gcm_sha_256,"
      "rsa_aes_256_gcm_sha_384,"
      "rsa_aes_128_sha,"
      "rsa_aes_256_sha",
    .http_headers = {
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:102.0) Gecko/20100101 Firefox/102.0",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
      "Accept-Language: en-US,en;q=0.5",
      "Accept-Encoding: gzip, deflate, br",
      "Upgrade-Insecure-Requests: 1",
      "Sec-Fetch-Dest: document",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-User: ?1",
      "TE: Trailers"
    }
  },
  {
    .target = "ff109",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "aes_128_gcm_sha_256,"
      "chacha20_poly1305_sha_256,"
      "aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_128_gcm_sha_256,"
      "ecdhe_rsa_aes_128_gcm_sha_256,"
      "ecdhe_ecdsa_chacha20_poly1305_sha_256,"
      "ecdhe_rsa_chacha20_poly1305_sha_256,"
      "ecdhe_ecdsa_aes_256_gcm_sha_384,"
      "ecdhe_rsa_aes_256_gcm_sha_384,"
      "ecdhe_ecdsa_aes_256_sha,"
      "ecdhe_ecdsa_aes_128_sha,"
      "ecdhe_rsa_aes_128_sha,"
      "ecdhe_rsa_aes_256_sha,"
      "rsa_aes_128_gcm_sha_256,"
      "rsa_aes_256_gcm_sha_384,"
      "rsa_aes_128_sha,"
      "rsa_aes_256_sha",
    .http_headers = {
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/109.0",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
      "Accept-Language: en-US,en;q=0.5",
      "Accept-Encoding: gzip, deflate, br",
      "Upgrade-Insecure-Requests: 1",
      "Sec-Fetch-Dest: document",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-User: ?1",
      "TE: Trailers"
    }
  },
  {
    /* Last one must be NULL. */
    .target = NULL
  }
};
