#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "nghttp2_session.h"
#include <string.h>

#include "nghttp2_test_helper.h"
}

void check_session_send(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  int rv;

  session = nghttp2_session_new();
  if (session == NULL) {
    return;
  }

  /* Create a set of headers seeded with data from the fuzzer */
  std::vector<uint8_t> bytes = data_provider->ConsumeRemainingBytes();
  void *data_ptr = bytes.data();

  /* Perform a set of operations with the fuzz data */
  rv = nghttp2_session_send(session, (const uint8_t *)data_ptr, bytes.size());
  if (rv < 0) {
    return;
  }

  /* Cleanup */
  nghttp2_session_del(session);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_session_send(&data_provider);
  return 0;
}
```

The issue in the original code was that the header `#include "nghttp2_session.h"` was not wrapped with `extern "C" {}`. This caused the linker to be unable to find the definition of the `nghttp2_session_send` function, which is declared in `nghttp2_session.h`.

To fix the issue, the header `#include "nghttp2_session.h"` was wrapped with `extern "C" {}`. This tells the linker to look for the definition of the `nghttp2_session_send` function in the C language, rather than the C++ language.