#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a new session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  // Consume an integer from the input data for the second parameter
  int bye_type = stream.ConsumeIntegral<int>();

  // Call the target function
  gnutls_bye(session, bye_type);

  // Clean up
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}