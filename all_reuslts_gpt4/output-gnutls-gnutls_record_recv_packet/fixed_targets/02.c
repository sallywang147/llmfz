#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>
#include <gnutls/mbuffer.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);

  // Call the target function
  struct mbuffer_st *mbuffer = nullptr;
  size_t result = gnutls_record_recv_packet(session, &mbuffer);

  // Clean up
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}