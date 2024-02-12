 #include <stddef.h>
#include <stdint.h>

#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_session_t session;
  gnutls_certificate_credentials_t xcred;
  gnutls_datum_t ca;
  gnutls_x509_crt_t crt;
  int ret;

  gnutls_global_init();

  ret = gnutls_certificate_allocate_credentials(&xcred);
  if (ret < 0) {
    return 0;
  }

  ca.data = (unsigned char*)data;
  ca.size = size;

  ret = gnutls_x509_crt_init(&crt);
  if (ret < 0) {
    return 0;
  }

  ret = gnutls_x509_crt_import(crt, &ca, GNUTLS_X509_FMT_DER);
  if (ret < 0) {
    gnutls_x509_crt_deinit(crt);
    return 0;
  }

  ret = gnutls_certificate_set_x509_trust(xcred, crt);
  if (ret < 0) {
    gnutls_x509_crt_deinit(crt);
    return 0;
  }

  ret = gnutls_init(&session, GNUTLS_SERVER);
  if (ret < 0) {
    gnutls_x509_crt_deinit(crt);
    return 0;
  }

  ret = gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, xcred);
  if (ret < 0) {
    gnutls_deinit(session);
    gnutls_x509_crt_deinit(crt);
    return 0;
  }

  gnutls_bye(session, GNUTLS_SHUT_RDWR);

  gnutls_deinit(session);
  gnutls_certificate_free_credentials(xcred);
  gnutls_x509_crt_deinit(crt);

  return 0;
}