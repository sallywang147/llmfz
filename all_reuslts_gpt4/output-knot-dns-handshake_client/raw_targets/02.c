#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a new session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);

  // Set up the session
  FuzzedDataProvider stream(data, size);
  std::string server_name = stream.ConsumeRandomLengthString();
  gnutls_server_name_set(session, GNUTLS_NAME_DNS, server_name.c_str(), server_name.size());

  // Perform the handshake
  handshake_client(session);

  // Deinitialize session and GnuTLS library
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}