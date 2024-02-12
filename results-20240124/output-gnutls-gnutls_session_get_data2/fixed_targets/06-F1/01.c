#include <assert.h>
#include <stdint.h>

#include <gnutls/gnutls.h>
#include <gnutls/session.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer.h"

extern "C" {
#include <alloca.h>
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_datum_t datum;
  gnutls_session_t session;
  int ret;

  ret = gnutls_init(&session, GNUTLS_CLIENT);
  assert(ret >= 0);

  datum.data = (unsigned char*)data;
  datum.size = size;

  ret = gnutls_session_get_data2(session, &datum);
  assert(ret >= 0);

  gnutls_deinit(session);

  return 0;
}