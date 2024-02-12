#include <stdint.h>
#include <stddef.h>
#include <gnutls/gnutls.h>
#include "fuzzer.h"

extern "C" {
#include <stdbool.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_session_set_data(session, (void*)data, size);
  char buffer[1024];
  size_t len = sizeof(buffer);
  gnutls_session_get_data(session, buffer, &len);
  gnutls_deinit(session);
  return 0;
}