#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <gnutls/gnutls.h>
#include <gnutls/handshake.h> // Include the handshake header

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_global_init();

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);

  gnutls_priority_set_direct(session, "NORMAL", nullptr);

  const size_t cert_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const uint8_t* cert_data = stream.ConsumeBytes<uint8_t>(cert_size).data();
  gnutls_certificate_set_x509(session, cert_data, cert_size);

  const size_t key_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const uint8_t* key_data = stream.ConsumeBytes<uint8_t>(key_size).data();
  gnutls_privkey_set(session, GNUTLS_PRIVKEY_RSA, key_data, key_size, nullptr);

  const size_t hostname_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const uint8_t* hostname_data = stream.ConsumeBytes<uint8_t>(hostname_size).data();
  gnutls_server_name_set(session, GNUTLS_NAME_DNS, hostname_data, hostname_size);

  gnutls_handshake_set_timeout(session, GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

  // Call the handshake_client function
  int ret = gnutls_handshake_client(session);
  if (ret < 0) {
    gnutls_deinit(session);
    gnutls_global_deinit();
    return 0;
  }

  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}
```

The build error message indicates that the `gnutls_handshake_client` function is not defined. This is because the header file `gnutls/handshake.h` is not included in the code. To fix this, add the following line at the beginning of the code:

```c++
#include <gnutls/handshake.h>
```

This will include the necessary header file and allow the code to compile successfully.