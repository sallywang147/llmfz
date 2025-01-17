#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "lz4hc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  const size_t max_dst_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  const int c_level = stream.ConsumeIntegralInRange<int>(0, 16);
  std::vector<char> src_buffer(src_size);
  stream.ConsumeBytes<char>(src_buffer.data(), src_buffer.size());
  std::vector<char> dst_buffer(max_dst_size);

  const int ret = LZ4_compressHC2_limitedOutput(
      src_buffer.data(), dst_buffer.data(), src_buffer.size(), max_dst_size,
      c_level);
  return 0;
}
```

The build issue is caused by the missing `extern "C"` block around the `#include "lz4hc.h"` directive. This is necessary because the `lz4hc.h` header file contains C functions and data structures that need to be declared as `extern "C"` in order to be visible to the C++ compiler.

The fixed code includes the `extern "C"` block around the `#include "lz4hc.h"` directive, which allows the C++ compiler to see the C functions and data structures in the header file.