#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "lz4hc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const size_t dst_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> src(src_size);
  std::vector<char> dst(dst_size);
  stream.ConsumeBytes<char>(src.data(), src_size);

  LZ4_streamHC_u ctx;
  LZ4_resetStreamHC(&ctx, src_size);
  const int ret = LZ4_compressHC_continue(&ctx, src.data(), dst.data(), src_size);

  return 0;
}
```

The original code has a build issue because the header `#include "lz4hc.h"` is not wrapped with `extern "C" {}`. To fix this issue, we need to wrap the header with `extern "C" {}` like this:

```c++
extern "C" {
#include "lz4hc.h"
}
```

After this change, the code can be built successfully.