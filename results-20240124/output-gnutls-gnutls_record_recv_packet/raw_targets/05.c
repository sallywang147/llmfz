 #include <stdint.h>
#include <stdlib.h>
#include <gnutls/gnutls.h>
#include <gnutls/record.h>
#include "fuzzer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  gnutls_session_int session;
  struct mbuffer_st *mbuf;
  gnutls_record_recv_packet(&session, &mbuf);
  return 0;
}