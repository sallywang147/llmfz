#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "zstd.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (!cctx) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  size_t remaining = size;
  while (remaining > 0) {
    size_t consumed = provider.ConsumeIntegralInRange<size_t>(0, remaining);
    ZSTD_inBuffer input = {provider.ConsumeBytes<unsigned char>(consumed).data(), consumed, 0};
    size_t const ret = ZSTD_compressStream(cctx, &input, ZSTD_e_continue);
    if (ZSTD_isError(ret)) {
      fprintf(stderr, "ZSTD_compressStream error: %s\n", ZSTD_getErrorName(ret));
      ZSTD_freeCCtx(cctx);
      return 0;
    }
    remaining -= consumed;
  }

  ZSTD_inBuffer input = {nullptr, 0, 0};
  size_t const ret = ZSTD_compressStream(cctx, &input, ZSTD_e_end);
  if (ZSTD_isError(ret)) {
    fprintf(stderr, "ZSTD_compressStream error: %s\n", ZSTD_getErrorName(ret));
  }
  ZSTD_freeCCtx(cctx);

  return 0;
}
```

Changes made:
1. Changed `ZSTD_e_end` to `ZSTD_e_continue` in the `ZSTD_compressStream` call inside the loop. This ensures that the compression continues for each consumed chunk of data.
2. Added another call to `ZSTD_compressStream` with `ZSTD_e_end` to flush the remaining data and complete the compression.