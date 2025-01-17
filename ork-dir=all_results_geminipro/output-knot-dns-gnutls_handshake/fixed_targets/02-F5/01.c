#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  gnutls_session_t session;
  gnutls_certificate_credentials_t x509_cred;
  gnutls_priority_t priority_cache;

  // Initialize the global GnuTLS context.
  gnutls_global_init();

  // Allocate credentials.
  gnutls_certificate_allocate_credentials(&x509_cred);

  // Initialize the priority cache.
  gnutls_priority_init(&priority_cache, NULL, NULL);

  // Initialize the TLS session.
  gnutls_init(&session, GNUTLS_CLIENT);

  // Set the priority cache.
  gnutls_priority_set(session, priority_cache);

  // Set the credentials.
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, x509_cred);

  // Set random data.
  std::vector<uint8_t> random_data = provider.ConsumeBytes<uint8_t>(16);
  gnutls_rnd_set(session, random_data.data(), random_data.size());

  // Set the server name.
  std::string server_name = provider.ConsumeRemainingBytesAsString();
  gnutls_server_name_set(session, GNUTLS_NAME_DNS, server_name.c_str(),
                         server_name.size());

  // Perform the handshake.
  int ret = gnutls_handshake(session);
  if (ret < 0) {
    // Handshake failed.
    gnutls_deinit(session);
    gnutls_certificate_free_credentials(x509_cred);
    gnutls_priority_deinit(priority_cache);
    gnutls_global_deinit();
    return 0;
  }

  // Clean up.
  gnutls_deinit(session);
  gnutls_certificate_free_credentials(x509_cred);
  gnutls_priority_deinit(priority_cache);
  gnutls_global_deinit();

  return 0;
}