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
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);

  gnutls_transport_set_push_function(session, [](gnutls_transport_ptr_t, const void* data, size_t size) -> ssize_t {
    return size;
  });
  gnutls_transport_set_pull_function(session, [](gnutls_transport_ptr_t, void* data, size_t size) -> ssize_t {
    if (next_input.size() == 0) {
      return 0;
    }
    size_t copy_size = std::min(next_input.size(), size);
    memcpy(data, next_input.data(), copy_size);
    next_input.erase(next_input.begin(), next_input.begin() + copy_size);
    return copy_size;
  });

  handshake_client((struct gnutls_session_int*)session);

  gnutls_deinit(session);

  return 0;
}