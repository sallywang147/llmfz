#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "nghttp2_session.h"
#include <string.h>

#include "nghttp2_test_helper.h"

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
  rv = nghttp2_session_send(session, data_ptr, bytes.size());
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

} // extern C
```

The original code has the following issues:

1. The `nghttp2_session_new` function is not wrapped in `extern "C" {}`. This can cause linker errors when compiling the code.
2. The `nghttp2_session_del` function is not wrapped in `extern "C" {}`. This can also cause linker errors when compiling the code.

To fix these issues, we need to wrap both functions in `extern "C" {}`. The corrected code is shown above.