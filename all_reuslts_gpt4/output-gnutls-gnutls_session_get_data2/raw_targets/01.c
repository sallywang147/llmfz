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
  gnutls_datum_t datum;

  int ret = gnutls_init(&session, GNUTLS_CLIENT);
  if (ret != GNUTLS_E_SUCCESS) {
    return 0;
  }

  std::vector<uint8_t> buffer = provider.ConsumeRemainingBytes<uint8_t>();
  datum.data = buffer.data();
  datum.size = buffer.size();

  gnutls_session_get_data2(session, &datum);

  gnutls_deinit(session);

  return 0;
}