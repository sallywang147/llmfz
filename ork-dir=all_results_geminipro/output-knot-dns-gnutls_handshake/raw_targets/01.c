#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  gnutls_priority_set_direct(session, "NORMAL", NULL);
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE,
                         gnutls_x509_crt_init(),
                         gnutls_x509_privkey_init());

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

  gnutls_deinit(session);
  return 0;
}