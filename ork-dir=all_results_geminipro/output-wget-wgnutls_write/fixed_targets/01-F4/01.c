#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <wgnutls/wgnutls.h>

extern "C" {
  int wgnutls_write(int fd, const void *buf, size_t n, void *arg);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const int bufsize = stream.ConsumeIntegralInRange<int>(1, 1024);
  char* buf = new char[bufsize];
  const int arg_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  char* arg = new char[arg_size];
  stream.ConsumeData(buf, bufsize);
  stream.ConsumeData(arg, arg_size);
  wgnutls_write(fd, buf, bufsize, arg);  // Fix: Remove the '&' before 'arg'
  delete[] buf;
  delete[] arg;
  return 0;
}
```

The issue was that the `wgnutls_write` function expects a `void*` argument, but the code was passing a `char**` (a pointer to a pointer to a character). This caused the build error.

The fix was to remove the `&` before `arg` in the call to `wgnutls_write`. This ensures that the function is passed a `void*` argument, as expected.