 #include <assert.h>
#include <stdint.h>

#include <gnutls/gnutls.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_session_t session;
  int ret;

  ret = gnutls_init(&session, GNUTLS_CLIENT);
  assert(ret >= 0);

  gnutls_bye(session, GNUTLS_SHUT_RDWR);

  gnutls_deinit(session);
  return 0;
}