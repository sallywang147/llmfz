#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a new session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);

  // Consume data from the fuzzer input
  int ms = stream.ConsumeIntegral<int>();

  // Call the target function
  check_session_status(session, ms);

  // Deinitialize session and GnuTLS library
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}