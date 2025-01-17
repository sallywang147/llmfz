 #include <stdint.h>
#include <stdio.h>

#include <gnutls/gnutls.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  gnutls_session_t session;
  int ret;

  ret = gnutls_init(&session, GNUTLS_CLIENT);
  if (ret < 0) {
    return 0;
  }

  gnutls_bye(session, GNUTLS_SHUT_RDWR);

  gnutls_deinit(session);

  return 0;
}