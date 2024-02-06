#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int gnutls_session_get_data2(gnutls_session_t session, gnutls_datum_t *data, int type);
extern "C" int gnutls_init(gnutls_session_t *session, unsigned int session_type);
extern "C" int gnutls_deinit(gnutls_session_t session);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t session_type = stream.ConsumeIntegral<uint8_t>();
  gnutls_session_t session;
  gnutls_init(&session, session_type);
  const uint8_t data_type = stream.ConsumeIntegral<uint8_t>();
  gnutls_datum_t datum;
  datum.data = nullptr;
  datum.size = 0;
  const int result = gnutls_session_get_data2(session, &datum, data_type);
  gnutls_deinit(session);
  free(datum.data);
  return result;
}