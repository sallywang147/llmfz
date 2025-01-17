#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  gnutls_session_int* session;
  gnutls_init(&session, GNUTLS_CLIENT);

  FuzzedDataProvider provider(data, size);

  size_t buffer_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> buffer(buffer_size);
  char* seq = provider.ConsumeRemainingBytesAsString().c_str();

  gnutls_record_recv_seq(session, buffer.data(), buffer_size, seq);

  gnutls_deinit(session);

  return 0;
}