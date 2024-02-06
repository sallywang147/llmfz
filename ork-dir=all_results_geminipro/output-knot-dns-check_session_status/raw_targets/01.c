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
  const int ms = stream.ConsumeIntegralInRange<int>(0, 10000);
  check_session_status(session, ms);
  gnutls_session_free(session);
  return 0;
}