#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "buf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buf_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  struct Buf* buf = buf_new(buf_size);
  if (buf == nullptr) {
    return 0;
  }

  const size_t fmt_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char* fmt = static_cast<char*>(malloc(fmt_size + 1));  // Fix: Add 1 for null-terminator
  if (fmt == nullptr) {
    buf_free(buf);
    return 0;
  }
  stream.ConsumeBytes(fmt, fmt_size);
  fmt[fmt_size] = '\0';  // Fix: Add null-terminator

  const size_t s_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char* s = static_cast<char*>(malloc(s_size + 1));  // Fix: Add 1 for null-terminator
  if (s == nullptr) {
    buf_free(buf);
    free(fmt);
    return 0;
  }
  stream.ConsumeBytes(s, s_size);
  s[s_size] = '\0';  // Fix: Add null-terminator

  buf_prints(buf, fmt, s);

  buf_free(buf);
  free(fmt);
  free(s);
  return 0;
}
```

In this fixed code, the following issues are addressed:

- **Null-terminator for `fmt` and `s`**: In the original code, the `fmt` and `s` buffers were allocated without adding space for a null-terminator. This could lead to undefined behavior when using these buffers with functions that expect null-terminated strings. To fix this, `fmt_size` and `s_size` are incremented by 1 to accommodate the null-terminator, and the null-terminator is explicitly added to both buffers after consuming bytes from the stream.

With these changes, the code should now compile and run as intended.