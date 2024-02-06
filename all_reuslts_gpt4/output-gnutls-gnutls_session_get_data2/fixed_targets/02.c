#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  gnutls_session_t session;
  gnutls_datum_t session_data;

  int ret = gnutls_init(&session, GNUTLS_CLIENT);
  if(ret != GNUTLS_E_SUCCESS) {
    return 0;
  }

  // Consume some data for the session
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
  gnutls_record_recv(session, next_input.data(), next_input.size());

  // Call the target function
  gnutls_session_get_data2(session, &session_data);

  gnutls_deinit(session);
  gnutls_free(session_data.data);

  return 0;
}