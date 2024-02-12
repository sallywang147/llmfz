 #include <assert.h>
#include <stdint.h>

#include <gnutls/gnutls.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_datum_t out;
  gnutls_session_t session;
  int ret;

  ret = gnutls_init(&session, GNUTLS_CLIENT);
  assert(ret >= 0);

  out.data = (unsigned char *)data;
  out.size = size;

  ret = gnutls_session_get_data2(session, &out);
  if (ret < 0)
    goto fail;

fail:
  gnutls_deinit(session);
  return 0;
}