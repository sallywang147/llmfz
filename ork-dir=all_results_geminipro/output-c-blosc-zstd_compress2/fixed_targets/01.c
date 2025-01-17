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
      ZSTD_compress2(cctx, dest, dest_capacity, src, src_size, 1);
  ZSTD_freeCCtx(cctx);
  std::free(dest);
  return compressed_size;
}
```

The original code used `ZSTD_compressCCtx` instead of `ZSTD_compress2`. The latter is the correct function to use for compression with a compression context.