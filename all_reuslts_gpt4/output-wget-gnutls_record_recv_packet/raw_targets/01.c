#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "gnutls/gnutls.h"
#include "gnutls/mbuffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  // Set the session data
  std::vector<uint8_t> session_data = provider.ConsumeRemainingBytes<uint8_t>();
  gnutls_transport_set_ptr(session, session_data.data());

  // Call the target function
  struct mbuffer_st *packet = nullptr;
  gnutls_record_recv_packet(session, &packet);

  // Cleanup
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}