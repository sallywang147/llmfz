 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer.h"
#include "gnutls/gnutls.h"

size_t gnutls_record_recv_packet(struct gnutls_session_int *, struct mbuffer_st **);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct gnutls_session_int session;
  struct mbuffer_st *buf = NULL;
  size_t ret;

  gnutls_session_init(&session);
  ret = gnutls_record_recv_packet(&session, &buf);
  gnutls_session_deinit(&session);
  if (buf) mbuffer_free(buf);

  return 0;
}