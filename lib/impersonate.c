#include "curl_setup.h"

#include <curl/curl.h>

#include "impersonate.h"

const struct impersonate_opts impersonations[] = {
  {
    .target = "chrome99",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"99\", \"Google Chrome\";v=\"99\"",
      "sec-ch-ua-mobile: ?0",
      "sec-ch-ua-platform: \"Windows\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    }
  },
  {
    .target = "chrome100",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"100\", \"Google Chrome\";v=\"100\"",
      "sec-ch-ua-mobile: ?0",
      "sec-ch-ua-platform: \"Windows\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.75 Safari/537.36",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    }
  },
  {
    .target = "chrome101",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"101\", \"Google Chrome\";v=\"101\"",
      "sec-ch-ua-mobile: ?0",
      "sec-ch-ua-platform: \"Windows\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.67 Safari/537.36",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    }
  },
  {
    .target = "chrome104",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \"Chromium\";v=\"104\", \" Not A;Brand\";v=\"99\", \"Google Chrome\";v=\"104\"",
      "sec-ch-ua-mobile: ?0",
      "sec-ch-ua-platform: \"Windows\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    }
  },
  {
    .target = "chrome107",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \"Google Chrome\";v=\"107\", \"Chromium\";v=\"107\", \"Not=A?Brand\";v=\"24\"",
      "sec-ch-ua-mobile: ?0",
      "sec-ch-ua-platform: \"Windows\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    },
    .http2_no_server_push = true
  },
  {
      .target = "chrome110",
      .httpversion = CURL_HTTP_VERSION_2_0,
      .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
      .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
      .npn = false,
      .alpn = true,
      .alps = true,
      .tls_permute_extensions = true,
      .tls_session_ticket = true,
      .cert_compression = "brotli",
      .http_headers = {
              "sec-ch-ua: \"Chromium\";v=\"110\", \"Not A(Brand\";v=\"24\", \"Google Chrome\";v=\"110\"",
              "sec-ch-ua-mobile: ?0",
              "sec-ch-ua-platform: \"Windows\"",
              "Upgrade-Insecure-Requests: 1",
              "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36",
              "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
              "Sec-Fetch-Site: none",
              "Sec-Fetch-Mode: navigate",
              "Sec-Fetch-User: ?1",
              "Sec-Fetch-Dest: document",
              "Accept-Encoding: gzip, deflate, br",
              "Accept-Language: en-US,en;q=0.9"
      },
      .http2_no_server_push = true
  },
  {
      .target = "chrome116",
      .httpversion = CURL_HTTP_VERSION_2_0,
      .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
      .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
      .npn = false,
      .alpn = true,
      .alps = true,
      .tls_permute_extensions = true,
      .tls_session_ticket = true,
      .cert_compression = "brotli",
      .http_headers = {
              "sec-ch-ua: \"Chromium\";v=\"116\", \"Not)A;Brand\";v=\"24\", \"Google Chrome\";v=\"116\"",
              "sec-ch-ua-mobile: ?0",
              "sec-ch-ua-platform: \"Windows\"",
              "Upgrade-Insecure-Requests: 1",
              "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36",
              "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7",
              "Sec-Fetch-Site: none",
              "Sec-Fetch-Mode: navigate",
              "Sec-Fetch-User: ?1",
              "Sec-Fetch-Dest: document",
              "Accept-Encoding: gzip, deflate, br",
              "Accept-Language: en-US,en;q=0.9"
      },
      .http2_no_server_push = true
  },
  {
    .target = "chrome99_android",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"99\", \"Google Chrome\";v=\"99\"",
      "sec-ch-ua-mobile: ?1",
      "sec-ch-ua-platform: \"Android\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Linux; Android 12; Pixel 6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.58 Mobile Safari/537.36",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    }
  },
  {
    .target = "edge99",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"99\", \"Microsoft Edge\";v=\"99\"",
      "sec-ch-ua-mobile: ?0",
      "sec-ch-ua-platform: \"Windows\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36 Edg/99.0.1150.30",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    }
  },
  {
    .target = "edge101",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "ECDHE-ECDSA-AES128-GCM-SHA256,"
      "ECDHE-RSA-AES128-GCM-SHA256,"
      "ECDHE-ECDSA-AES256-GCM-SHA384,"
      "ECDHE-RSA-AES256-GCM-SHA384,"
      "ECDHE-ECDSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-CHACHA20-POLY1305,"
      "ECDHE-RSA-AES128-SHA,"
      "ECDHE-RSA-AES256-SHA,"
      "AES128-GCM-SHA256,"
      "AES256-GCM-SHA384,"
      "AES128-SHA,"
      "AES256-SHA",
    .npn = false,
    .alpn = true,
    .alps = true,
    .tls_session_ticket = true,
    .cert_compression = "brotli",
    .http_headers = {
      "sec-ch-ua: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"101\", \"Microsoft Edge\";v=\"101\"",
      "sec-ch-ua-mobile: ?0",
      "sec-ch-ua-platform: \"Windows\"",
      "Upgrade-Insecure-Requests: 1",
      "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.64 Safari/537.36 Edg/101.0.1210.47",
      "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
      "Sec-Fetch-Site: none",
      "Sec-Fetch-Mode: navigate",
      "Sec-Fetch-User: ?1",
      "Sec-Fetch-Dest: document",
      "Accept-Encoding: gzip, deflate, br",
      "Accept-Language: en-US,en;q=0.9"
    }
  },
  {
    .target = "safari15_3",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_0 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
        "TLS_AES_128_GCM_SHA256,"
        "TLS_AES_256_GCM_SHA384,"
        "TLS_CHACHA20_POLY1305_SHA256,"
        "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,"
        "TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,"
        "TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,"
        "TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,"
        "TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,"
        "TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,"
        "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384,"
        "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256,"
        "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA,"
        "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA,"
        "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384,"
        "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256,"
        "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,"
        "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,"
        "TLS_RSA_WITH_AES_256_GCM_SHA384,"
        "TLS_RSA_WITH_AES_128_GCM_SHA256,"
        "TLS_RSA_WITH_AES_256_CBC_SHA256,"
        "TLS_RSA_WITH_AES_128_CBC_SHA256,"
        "TLS_RSA_WITH_AES_256_CBC_SHA,"
        "TLS_RSA_WITH_AES_128_CBC_SHA,"
        "TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA,"
        "TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA,"
        "TLS_RSA_WITH_3DES_EDE_CBC_SHA,",
    .curves = "X25519:P-256:P-384:P-521",
    .sig_hash_algs =
        "ecdsa_secp256r1_sha256,"
        "rsa_pss_rsae_sha256,"
        "rsa_pkcs1_sha256,"
        "ecdsa_secp384r1_sha384,"
        "ecdsa_sha1,"
        "rsa_pss_rsae_sha384,"
        "rsa_pss_rsae_sha384,"
        "rsa_pkcs1_sha384,"
        "rsa_pss_rsae_sha512,"
        "rsa_pkcs1_sha512,"
        "rsa_pkcs1_sha1",
    .npn = false,
    .alpn = true,
    .alps = false,
    .tls_session_ticket = false,
    .http_headers = {
        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/15.3 Safari/605.1.15",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-us",
        "Accept-Encoding: gzip, deflate, br"
    },
    .http2_pseudo_headers_order = "mspa"
  },
  {
    .target = "safari15_5",
    .httpversion = CURL_HTTP_VERSION_2_0,
    .ssl_version = CURL_SSLVERSION_TLSv1_0 | CURL_SSLVERSION_MAX_DEFAULT,
    .ciphers =
      "TLS_AES_128_GCM_SHA256,"
      "TLS_AES_256_GCM_SHA384,"
      "TLS_CHACHA20_POLY1305_SHA256,"
      "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,"
      "TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,"
      "TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,"
      "TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,"
      "TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,"
      "TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,"
      "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA,"
      "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA,"
      "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,"
      "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,"
      "TLS_RSA_WITH_AES_256_GCM_SHA384,"
      "TLS_RSA_WITH_AES_128_GCM_SHA256,"
      "TLS_RSA_WITH_AES_256_CBC_SHA,"
      "TLS_RSA_WITH_AES_128_CBC_SHA,"
      "TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA,"
      "TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA,"
      "TLS_RSA_WITH_3DES_EDE_CBC_SHA",
    .curves = "X25519:P-256:P-384:P-521",
    .sig_hash_algs =
      "ecdsa_secp256r1_sha256,"
      "rsa_pss_rsae_sha256,"
      "rsa_pkcs1_sha256,"
      "ecdsa_secp384r1_sha384,"
      "ecdsa_sha1,"
      "rsa_pss_rsae_sha384,"
      "rsa_pss_rsae_sha384,"
      "rsa_pkcs1_sha384,"
      "rsa_pss_rsae_sha512,"
      "rsa_pkcs1_sha512,"
      "rsa_pkcs1_sha1",
    .npn = false,
    .alpn = true,
    .alps = false,
    .tls_session_ticket = false,
    .cert_compression = "zlib",
    .http_headers = {
        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/15.5 Safari/605.1.15",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en-US;q=0.9,en;q=0.8",
        "Accept-Encoding: gzip, deflate, br"
    },
    .http2_pseudo_headers_order = "mspa"
  },
  {
    /* Last one must be NULL. */
    .target = NULL
  }
};
