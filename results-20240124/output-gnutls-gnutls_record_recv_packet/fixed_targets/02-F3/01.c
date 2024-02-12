#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <gnutls/gnutls.h>
#include <gnutls/mbuf.h>

#include "fuzzer.h"

extern "C" {
#include <alloca.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  gnutls_session_int session;
  struct mbuffer_st *mbuf;
  size_t ret;

  gnutls_session_init(&session);
  gnutls_session_set_ptr(session, data, size);

  ret = gnutls_record_recv_packet(&session, &mbuf);
  if (ret != 0) {
    gnutls_session_deinit(&session);
    return 0;
  }

  gnutls_session_deinit(&session);
  mbuf_free(mbuf);

  return 0;
}