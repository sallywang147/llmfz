#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "lz4.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  const size_t dst_size = stream.ConsumeIntegralInRange<size_t>(0, 100000);
  const int c_level = stream.ConsumeIntegralInRange<int>(0, 16);
  char* src = new char[src_size];
  char* dst = new char[dst_size];
  stream.ConsumeBytes(src, src_size);
  const int result = LZ4_compressHC2(src, dst, src_size, c_level);
  delete[] src;
  delete[] dst;
  return result;
}
```

The build issue is caused by the missing `extern "C"` wrapper around the `#include` directive for the `lz4.h` header. This is necessary because the `LZ4_compressHC2` function is declared in C, and the C++ compiler needs to be instructed to use the C calling convention when calling it.

To fix the issue, the `#include` directive for `lz4.h` should be wrapped with `extern "C" {}`, like this:

```c++
extern "C" {
#include "lz4.h"
}
```

This tells the compiler that the `lz4.h` header contains C declarations, and that any functions or variables declared in that header should be treated as C functions or variables.

With this change, the code should compile and run correctly.