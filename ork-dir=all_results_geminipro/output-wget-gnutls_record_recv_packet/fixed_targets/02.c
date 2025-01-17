#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include <mbedtls/error.h>
#include <mbedtls/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  mbedtls_ssl_context ssl;
  mbedtls_ssl_init(&ssl);

  const int ret = mbedtls_ssl_setup(&ssl, mbedtls_ssl_get_ciphersuite_info(
                                          MBEDTLS_TLS_1_2_WITH_NULL_NULL));
  if (ret != 0) {
    mbedtls_ssl_free(&ssl);
    return 0;
  }

  mbedtls_ssl_set_bio(&ssl, nullptr, mbedtls_ssl_send, mbedtls_ssl_recv, nullptr);

  std::vector<uint8_t> output_buffer(MBEDTLS_SSL_MAX_CONTENT_LEN);
  size_t output_written = 0;

  // Initially, start by feeding the decoder more data.
  int decode_ret = MBEDTLS_ERR_SSL_WANT_READ;
  while (decode_ret == MBEDTLS_ERR_SSL_WANT_READ) {
    if (stream.remaining_bytes() == 0) {
      break;
    }
    const size_t next_size = stream.ConsumeIntegralInRange<size_t>(
        0,
        stream.remaining_bytes());
    auto next_input = stream.ConsumeBytes<unsigned char>(next_size);
    decode_ret = mbedtls_ssl_write(&ssl, next_input.data(), next_input.size());
  }

  if (decode_ret != 0) {
    mbedtls_ssl_free(&ssl);
    return 0;
  }

  struct mbuffer_st* packet = nullptr;
  const size_t bytes_received = mbedtls_ssl_read(&ssl, output_buffer.data(), output_buffer.size());
  if (bytes_received > 0) {
    output_written = bytes_received;
  }

  // Call mbedtls_ssl_read_record to fix the issue.
  mbedtls_ssl_read_record(&ssl, &packet);

  mbedtls_ssl_free(&ssl);

  return 0;
}