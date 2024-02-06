#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_global_init();
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);
  gnutls_priority_set_direct(session, "NORMAL", NULL);
  gnutls_certificate_allocate_credentials(&session);
  gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, gnutls_certificate_get(session));

  gnutls_transport_set_ptr(session, (gnutls_transport_ptr_t)data, size);
  gnutls_handshake(session);
  gnutls_deinit(session);
  gnutls_global_deinit();

  return 0;
}
```

In this code, the function `handshake_server` is not called, which is causing the build error. To fix this, the function `gnutls_handshake` is called instead, which performs the server-side handshake.