#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <gnutls/gnutls.h>
#include <gnutls/certificate.h>

extern "C" {
#include <gnutls/x509.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  gnutls_priority_set_direct(session, "NORMAL", NULL);

  // Initialize the certificate and private key.
  gnutls_certificate_credentials_t x509_cred;
  gnutls_certificate_allocate_credentials(&x509_cred);
  gnutls_certificate_set_x509_key_file(x509_cred, "cert.pem", "key.pem", GNUTLS_X509_FMT_PEM);

  // Set the credentials.
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, x509_cred);

  // Initialize the handshake.
  gnutls_handshake_set_timeout(session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);
  gnutls_handshake_set_post_handshake_auth(session, GNUTLS_HANDSHAKE_POST_HANDSHAKE_AUTH_REQUIRED);

  // Read and write data.
  while (stream.remaining_bytes() > 0) {
    size_t len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    auto data = stream.ConsumeBytes<uint8_t>(len);
    gnutls_transport_write(session, data.data(), data.size());

    // Process the data.
    int ret = gnutls_handshake(session);
    if (ret < 0) {
      gnutls_deinit(session);
      return 0;
    }
  }

  // Free the certificate credentials.
  gnutls_certificate_free_credentials(x509_cred);

  gnutls_deinit(session);
  return 0;
}