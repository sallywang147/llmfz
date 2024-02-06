#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mbedtls/ssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize mbedtls_ssl_context
  mbedtls_ssl_context ssl;
  mbedtls_ssl_init(&ssl);

  // Initialize mbedtls_ssl_config
  mbedtls_ssl_config conf;
  mbedtls_ssl_config_init(&conf);
  
  // Setup config
  if(mbedtls_ssl_config_defaults(&conf, 
                                 MBEDTLS_SSL_IS_CLIENT,
                                 MBEDTLS_SSL_TRANSPORT_STREAM, 
                                 MBEDTLS_SSL_PRESET_DEFAULT) != 0) {
    mbedtls_ssl_config_free(&conf);
    return 0;
  }

  // Setup SSL context
  if(mbedtls_ssl_setup(&ssl, &conf) != 0) {
    mbedtls_ssl_config_free(&conf);
    return 0;
  }

  // Consume data for mbedtls_ssl_write
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *buf = const_cast<char*>(str.c_str());
  size_t len = str.size();

  // Call the function to fuzz
  mbedtls_ssl_write(&ssl, buf, len);

  // Free resources
  mbedtls_ssl_free(&ssl);
  mbedtls_ssl_config_free(&conf);

  return 0;
}