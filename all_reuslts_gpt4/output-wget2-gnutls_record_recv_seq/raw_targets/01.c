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

  gnutls_session_t session;
  int ret = gnutls_init(&session, GNUTLS_CLIENT);
  if (ret != GNUTLS_E_SUCCESS) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  const size_t data_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  auto data_buffer = provider.ConsumeBytes<char>(data_size);
  char seq[8] = {0};

  gnutls_record_recv_seq(session, data_buffer.data(), data_buffer.size(), seq);

  gnutls_deinit(session);

  return 0;
}