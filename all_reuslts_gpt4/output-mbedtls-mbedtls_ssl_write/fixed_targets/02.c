#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mbedtls/ssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize mbedtls
  mbedtls_ssl_context ssl;
  mbedtls_ssl_init(&ssl);

  // Initialize SSL configuration
  mbedtls_ssl_config conf;
  mbedtls_ssl_config_init(&conf);
  if (mbedtls_ssl_config_defaults(&conf,
                                  MBEDTLS_SSL_IS_CLIENT,
                                  MBEDTLS_SSL_TRANSPORT_STREAM,
                                  MBEDTLS_SSL_PRESET_DEFAULT) != 0) {
    mbedtls_ssl_config_free(&conf);
    return 0;
  }

  mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, NULL);

  // Setup SSL context
  if (mbedtls_ssl_setup(&ssl, &conf) != 0) {
    mbedtls_ssl_config_free(&conf);
    return 0;
  }

  // Consume data to write
  std::string buf = stream.ConsumeRemainingBytesAsString();
  int ret = mbedtls_ssl_write(&ssl, buf.c_str(), buf.size());

  // Cleanup
  mbedtls_ssl_free(&ssl);
  mbedtls_ssl_config_free(&conf);

  return 0;
}