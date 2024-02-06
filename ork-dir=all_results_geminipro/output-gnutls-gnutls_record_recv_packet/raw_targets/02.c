#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t session_id_length = stream.ConsumeIntegral<uint8_t>();
  const uint8_t* session_id = stream.ConsumeBytes<uint8_t>(session_id_length);
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_set_default_priority(session);
  gnutls_session_set_data(session, session_id, session_id_length);

  gnutls_transport_ptr transport;
  gnutls_transport_set_ptr(&transport, nullptr);

  struct mbuffer_st* mbuffer = nullptr;
  const size_t data_length = stream.ConsumeIntegral<size_t>();
  const uint8_t* data_ptr = stream.ConsumeBytes<uint8_t>(data_length);
  const size_t result = gnutls_record_recv_packet(session, &mbuffer);
  if (result == GNUTLS_E_AGAIN) {
    gnutls_record_recv(session, data_ptr, data_length);
  }
  gnutls_deinit(session);
  gnutls_transport_deinit(transport);
  if (mbuffer != nullptr) {
    mbuf_free(mbuffer);
  }
  return 0;
}