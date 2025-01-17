#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "buffer.h"

extern "C" {
#include "hoedown.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t buffer_size = stream.ConsumeIntegral<uint8_t>();
  hoedown_buffer* buffer = hoedown_buffer_new(buffer_size);
  if (buffer == nullptr) {
    return 0;
  }

  const uint32_t codepoint = stream.ConsumeIntegral<uint32_t>();
  hoedown_buffer_put_utf8(buffer, codepoint);
  hoedown_buffer_free(buffer);
  return 0;
}
```

The build error message indicates that the function `hoedown_buffer_new`, `hoedown_buffer_put_utf8`, and `hoedown_buffer_free` are not defined. To fix this, we need to include the necessary header file, which is `hoedown.h`. However, since `hoedown.h` is a C header file, we need to wrap the `#include` directive with `extern "C" {}` to ensure that the C++ compiler does not mangle the function names.

After adding the `extern "C" {}` wrapper, the code should compile and run successfully.