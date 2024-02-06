#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize GnuTLS library
  gnutls_global_init();

  // Create a new session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  // Set up data provider
  FuzzedDataProvider dataProvider(data, size);

  // Consume data to fuzz the session
  while (dataProvider.remaining_bytes() > 0) {
    const uint8_t *currentData;
    size_t currentSize;
    std::tie(currentData, currentSize) = dataProvider.ConsumeData<uint8_t>(dataProvider.remaining_bytes());
    gnutls_record_recv(session, (void *)currentData, currentSize);
  }

  // Call the target function
  handshake_server((struct gnutls_session_int *)session);

  // Cleanup
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}