#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a new session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  // Consume data from the stream to use as input for the function
  int how = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  gnutls_bye(session, how);

  // Clean up
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}