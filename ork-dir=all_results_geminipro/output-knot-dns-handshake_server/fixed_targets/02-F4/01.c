#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  gnutls_priority_set_direct(session, "NORMAL", NULL);

  gnutls_certificate_credentials_t x509_cred;
  gnutls_certificate_credentials_init(&x509_cred);
  gnutls_certificate_set_x509_trust(x509_cred);
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, x509_cred);

  gnutls_dh_params_t dh_params;
  gnutls_dh_params_init(&dh_params);
  gnutls_dh_params_generate2(dh_params, GNUTLS_PK_DH);
  gnutls_dh_set_prime_bits(dh_params, 2048);
  gnutls_credentials_set_dh_params(session, GNUTLS_CRD_DH, dh_params);

  gnutls_rsa_key_t rsa_key;
  gnutls_rsa_key_init(&rsa_key);
  gnutls_rsa_generate_key(rsa_key, 2048, 65537);
  gnutls_credentials_set_x509_key(session, rsa_key);

  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> input_buffer = provider.ConsumeRemainingBytes<uint8_t>();

  int ret = gnutls_process_incoming_data(session, input_buffer.data(), input_buffer.size());
  if (ret != GNUTLS_E_AGAIN) {
    handshake_server(session);
    gnutls_deinit(session);
  }

  gnutls_certificate_credentials_deinit(x509_cred);
  gnutls_dh_params_deinit(dh_params);
  gnutls_rsa_key_deinit(rsa_key);

  return 0;
}

void handshake_server(gnutls_session_t session) {
  int ret;
  do {
    ret = gnutls_handshake(session);
  } while (ret == GNUTLS_E_AGAIN || ret == GNUTLS_E_INTERRUPTED);

  if (ret != 0) {
    fprintf(stderr, "Error in handshake: %s\n", gnutls_strerror(ret));
    exit(1);
  }
}