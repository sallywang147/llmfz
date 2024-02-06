#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gnutls_session_int* session = gnutls_session_new(nullptr);
  if (session == nullptr) {
    return 0;
  }

  size_t data_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> data_buffer(data_size);
  stream.ConsumeBytes(data_buffer.data(), data_buffer.size());

  size_t data_returned = 0;
  int ret = gnutls_session_set_data(session, data_buffer.data(), data_buffer.size());
  if (ret != 0) {
    gnutls_session_free(session);
    return 0;
  }

  gnutls_session_free(session);
  return 0;
}