#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  gnutls_certificate_credentials_t x509_cred;
  gnutls_certificate_allocate_credentials(&x509_cred);
  gnutls_certificate_set_x509_system_trust(x509_cred);

  gnutls_global_init();  // Changed from gnutls_init

  gnutls_session_t session;
  gnutls_session_init(&session);

  gnutls_session_set_ptr(session, GNUTLS_CRD_CERTIFICATE, x509_cred);

  gnutls_priority_set_direct(session, "NORMAL", nullptr);

  const char* hostname = provider.ConsumeRemainingBytesAsString().c_str();
  gnutls_server_name_t server_name;
  gnutls_server_name_init(&server_name);
  gnutls_server_name_set_hostname(&server_name, hostname);
  gnutls_session_set_server_name(session, &server_name);

  gnutls_session_set_verify_flags(session, GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT);

  gnutls_transport_set_ptr(session, (gnutls_transport_ptr_t)1);

  int ret = gnutls_handshake_client(session);
  if (ret < 0) {
    gnutls_perror(ret);
    gnutls_global_deinit();  // Changed from gnutls_deinit
    gnutls_certificate_free_credentials(x509_cred);
    return 0;
  }

  gnutls_global_deinit();  // Changed from gnutls_deinit
  gnutls_certificate_free_credentials(x509_cred);

  return 0;
}