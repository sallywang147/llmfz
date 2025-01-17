#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);
  gnutls_priority_set_direct(session, "NORMAL", NULL);
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE,
                        gnutls_x509_crt_read(
                            "gnutls-serv.crt", GNUTLS_X509_FMT_PEM),
                        gnutls_x509_privkey_read(
                            "gnutls-serv.key", GNUTLS_X509_FMT_PEM, NULL));
  gnutls_transport_set_ptr(session, (gnutls_transport_ptr_t)data, size);
  gnutls_record_recv_seq(session, NULL, 0, NULL);
  gnutls_deinit(session);
  return 0;
}