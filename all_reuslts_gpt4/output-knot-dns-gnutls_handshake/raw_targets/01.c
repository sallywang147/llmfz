#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  gnutls_session_t session;
  int ret = gnutls_init(&session, GNUTLS_SERVER);
  if (ret != GNUTLS_E_SUCCESS) {
    return 0;
  }

  gnutls_certificate_credentials_t x509_cred;
  ret = gnutls_certificate_allocate_credentials(&x509_cred);
  if (ret != GNUTLS_E_SUCCESS) {
    gnutls_deinit(session);
    return 0;
  }

  ret = gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, x509_cred);
  if (ret != GNUTLS_E_SUCCESS) {
    gnutls_certificate_free_credentials(x509_cred);
    gnutls_deinit(session);
    return 0;
  }

  gnutls_datum_t datum;
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
  datum.data = bytes.data();
  datum.size = bytes.size();

  gnutls_transport_set_push_function(session, [](gnutls_transport_ptr_t, const void*, size_t){ return 0; });
  gnutls_transport_set_pull_function(session, [](gnutls_transport_ptr_t, void*, size_t){ return 0; });
  gnutls_transport_set_ptr(session, &datum);

  gnutls_handshake(session);

  gnutls_certificate_free_credentials(x509_cred);
  gnutls_deinit(session);

  return 0;
}