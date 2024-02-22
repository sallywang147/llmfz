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

  // Flush the remaining data in the compressor.
  size_t const flush_ret = ZSTD_flushStream(cctx, &input);
  if (ZSTD_isError(flush_ret)) {
    fprintf(stderr, "ZSTD_flushStream error: %s\n", ZSTD_getErrorName(flush_ret));
  }

  ZSTD_freeCCtx(cctx);

  return 0;
}
```

Changes made:

1. Added a call to `ZSTD_flushStream` after the compression loop to flush the remaining data in the compressor.
2. Checked the return value of `ZSTD_flushStream` and printed an error message if it fails.