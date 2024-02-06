#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);
  struct mbuffer_st *packet;

  size_t ret = gnutls_record_recv_packet(session, &packet);
  if (ret != 0) {
    return 0;
  }

  if (packet) {
    gnutls_mbuf_free(packet);
  }

  gnutls_deinit(session);
  return 0;
}