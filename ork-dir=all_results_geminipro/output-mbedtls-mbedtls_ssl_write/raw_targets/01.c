#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "mbedtls/ssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  mbedtls_ssl_context ssl;
  mbedtls_ssl_init(&ssl);
  FuzzedDataProvider stream(data, size);
  size_t len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> input_buffer(len);
  stream.ConsumeBytes<uint8_t>(input_buffer.data(), len);
  mbedtls_ssl_write(&ssl, reinterpret_cast<char*>(input_buffer.data()), len);
  mbedtls_ssl_free(&ssl);
  return 0;
}