#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "zstd.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t dest_capacity = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  char* dest = static_cast<char*>(std::malloc(dest_capacity));
  if (dest == nullptr) {
    return 0;
  }
  ZSTD_CCtx* const cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    std::free(dest);
    return 0;
  }
  const size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, 1 << 20);
  const char* src = reinterpret_cast<const char*>(stream.ConsumeBytes<uint8_t>(src_size).data());
  const size_t compressed_size =
      ZSTD_compressCCtx(cctx, dest, dest_capacity, src, src_size, 1);  // Fix: Use ZSTD_compressCCtx instead of ZSTD_compress2.
  ZSTD_freeCCtx(cctx);
  std::free(dest);
  return compressed_size;
}
```

The issue in the original code was that it was using `ZSTD_compress2` instead of `ZSTD_compressCCtx` to compress the data. This resulted in a build error because `ZSTD_compress2` is not a valid function in the `zstd` library.

To fix the issue, we replaced `ZSTD_compress2` with `ZSTD_compressCCtx`, which is the correct function for compressing data using a compression context.