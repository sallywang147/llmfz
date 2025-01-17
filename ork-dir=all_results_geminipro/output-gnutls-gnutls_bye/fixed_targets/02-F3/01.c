#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_bye(session, GNUTLS_SHUT_RDWR);
  gnutls_deinit(session);
  return 0;
}
```

The fixed code is shown above. The only change is that the `gnutls.h` header is wrapped with `extern "C" {}`. This is necessary because the header file contains C-style function declarations, which are not compatible with C++ by default. By wrapping the header with `extern "C"`, we explicitly tell the compiler to treat the functions declared in the header as C-style functions, allowing the linking to succeed.