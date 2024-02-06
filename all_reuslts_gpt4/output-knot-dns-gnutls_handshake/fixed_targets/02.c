#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  gnutls_session_t session;
  int ret = gnutls_init(&session, GNUTLS_SERVER);
  if (ret != GNUTLS_E_SUCCESS) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  const std::string buffer = stream.ConsumeRemainingBytesAsString();
  gnutls_transport_set_push_function(session, [](gnutls_transport_ptr_t, const void*, size_t) {
    return 0;
  });
  gnutls_transport_set_pull_function(session, [](gnutls_transport_ptr_t, void*, size_t) {
    return 0;
  });
  gnutls_transport_set_ptr(session, (gnutls_transport_ptr_t)buffer.c_str());

  gnutls_handshake(session);

  gnutls_deinit(session);

  return 0;
}