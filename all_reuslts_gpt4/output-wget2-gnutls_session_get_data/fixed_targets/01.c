#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  FuzzedDataProvider stream(data, size);
  size_t session_data_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> session_data(session_data_size);

  gnutls_session_get_data(session, session_data.data(), &session_data_size);

  gnutls_deinit(session);

  return 0;
}