#include <fuzzer/FuzzedDataProvider.h>
#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_session_t session;
  int ret = gnutls_init(&session, GNUTLS_SERVER);
  if (ret < 0) {
    return 0;
  }

  gnutls_datum_t datum;
  datum.data = stream.ConsumeRemainingBytes<uint8_t>().data();
  datum.size = size;

  gnutls_transport_set_push_function(session, NULL);
  gnutls_transport_set_pull_function(session, NULL);
  gnutls_transport_set_ptr(session, &datum);

  handshake_server(session);

  gnutls_deinit(session);

  return 0;
}