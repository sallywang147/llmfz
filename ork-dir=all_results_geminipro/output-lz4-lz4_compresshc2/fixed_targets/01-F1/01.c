#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "lz4hc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* src = new char[src_size];
  stream.ConsumeBytes(src, src_size);

  const size_t dst_size = LZ4_compressBound(src_size);
  char* dst = new char[dst_size];

  const int c_level = stream.ConsumeIntegralInRange<int>(0, 16);
  LZ4_compressHC2(src, dst, src_size, c_level);

  delete[] src;
  delete[] dst;

  return 0;
}
```

The build issue is caused by the missing header file `cstring`. This header file is necessary for the `memset` function used in the `LZ4_compressHC2` function.

To fix the issue, add the following line to the beginning of the file:

```c++
#include <cstring>
```

This will include the necessary header file and allow the code to compile successfully.