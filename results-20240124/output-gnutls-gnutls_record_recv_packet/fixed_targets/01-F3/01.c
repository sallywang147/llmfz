#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <gnutls/gnutls.h>

#include "fuzzer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  gnutls_session_int session_int;
  mbuf_st *mbuf;

  gnutls_record_recv_packet(&session_int, &mbuf);

  return 0;
}