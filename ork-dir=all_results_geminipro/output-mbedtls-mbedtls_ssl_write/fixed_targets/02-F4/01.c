#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "mbedtls/ssl.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  mbedtls_ssl_context ssl;
  mbedtls_ssl_init(&ssl);
  mbedtls_ssl_setup(&ssl, mbedtls_ssl_get_ciphersuite_info(MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3));
  const std::string text = stream.ConsumeRemainingBytesAsString();
  mbedtls_ssl_write(&ssl, reinterpret_cast<unsigned char*>(const_cast<uint8_t*>(text.c_str())), text.size());
  mbedtls_ssl_close(&ssl);
  mbedtls_ssl_free(&ssl);
  return 0;
}