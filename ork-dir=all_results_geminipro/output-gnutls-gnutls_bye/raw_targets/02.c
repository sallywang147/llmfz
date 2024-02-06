#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_bye(session, GNUTLS_SHUT_RDWR);
  gnutls_deinit(session);
  return 0;
}