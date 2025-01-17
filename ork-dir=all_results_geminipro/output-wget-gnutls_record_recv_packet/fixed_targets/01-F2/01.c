#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gnutls_session_int session;
  memset(&session, 0, sizeof(session));
  struct mbuffer_st *packet;

  size_t ret = gnutls_record_recv_packet(&session, &packet);
  if (ret != 0) {
    return 0;
  }

  if (packet) {
    gnutls_mbuf_free(packet);
  }

  return 0;
}