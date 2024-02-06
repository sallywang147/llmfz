#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);
  gnutls_priority_set_direct(&session, "NORMAL", NULL);

  gnutls_certificate_credentials_t x509_cred;
  extern "C" gnutls_certificate_allocate_credentials(&x509_cred);

  gnutls_certificate_set_x509_system_trust(&x509_cred);
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, x509_cred);

  gnutls_dh_params_t dh_params;
  gnutls_dh_params_init(&dh_params);
  gnutls_dh_params_generate2(dh_params, 2048);
  gnutls_dh_set_params(session, dh_params);
  gnutls_dh_params_deinit(dh_params);

  gnutls_rsa_key_t rsa_key;
  gnutls_rsa_key_init(&rsa_key);
  gnutls_rsa_generate_key(&rsa_key, 2048, 65537);
  gnutls_rsa_set_key(session, GNUTLS_PRIVKEY_RSA, &rsa_key);
  gnutls_rsa_key_deinit(&rsa_key);

  struct mbuffer_st *packet = nullptr;
  size_t packet_size = gnutls_record_recv_packet(&session, &packet);
  if (packet_size > 0) {
    gnutls_record_release_packet(&session, &packet);
  }

  gnutls_bye(&session, GNUTLS_SHUT_RDWR);
  gnutls_deinit(&session);

  gnutls_certificate_free_credentials(x509_cred);

  return 0;
}