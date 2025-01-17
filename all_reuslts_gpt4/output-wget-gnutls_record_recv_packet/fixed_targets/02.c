#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gnutls/gnutls.h"
#include "gnutls/mbuffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a new session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  // Load the remaining bytes into the session
  std::vector<uint8_t> remaining_bytes = provider.ConsumeRemainingBytes<uint8_t>();
  gnutls_transport_set_ptr(session, static_cast<gnutls_transport_ptr_t>(remaining_bytes.data()));
  gnutls_transport_set_push_function(session, [](gnutls_transport_ptr_t ptr, const void* data, size_t len) {
    return len;
  });
  gnutls_transport_set_pull_function(session, [](gnutls_transport_ptr_t ptr, void* data, size_t len) {
    const uint8_t* source = static_cast<const uint8_t*>(ptr);
    memcpy(data, source, len);
    return len;
  });

  // Prepare packet
  struct mbuffer_st* packet = nullptr;

  // Call the function to fuzz
  gnutls_record_recv_packet(session, &packet);

  // Clean up
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}