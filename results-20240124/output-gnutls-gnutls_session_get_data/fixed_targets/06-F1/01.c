#include <assert.h>
#include <stdint.h>

#include <gnutls/gnutls.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer.h"

extern "C" {
#include <alloca.h>
#include <malloc.h>
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_session_t session;
  char buf[4096];
  size_t len = sizeof(buf);

  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_session_set_ptr(session, data, size);

  int ret = gnutls_session_get_data(session, buf, &len);
  assert(ret >= 0);

  gnutls_deinit(session);
  return 0;
}