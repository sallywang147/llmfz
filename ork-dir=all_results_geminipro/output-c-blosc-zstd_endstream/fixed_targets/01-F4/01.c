#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "zstd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (!cctx) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  ZSTD_inBuffer input = {nullptr, 0, 0};

  while (provider.remaining_bytes() > 0) {
    size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0, provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
    input.src = next_input.data();
    input.size = next_input.size();
    input.pos = 0;
    while (input.pos < input.size) {
      size_t ret = ZSTD_compressStream(cctx, &input, ZSTD_e_continue);
      if (ZSTD_isError(ret)) {
        fprintf(stderr, "ZSTD_compressStream error: %s\n", ZSTD_getErrorName(ret));
        ZSTD_freeCCtx(cctx);
        return 0;
      }
    }
  }

  size_t ret = ZSTD_endStream(cctx, &input);
  if (ZSTD_isError(ret)) {
    fprintf(stderr, "ZSTD_endStream error: %s\n", ZSTD_getErrorName(ret));
  }

  ZSTD_freeCCtx(cctx);

  return 0;
}
```

The issue in the original code is that `ZSTD_compressStream` is called with `ZSTD_e_end` instead of `ZSTD_e_continue` in the inner loop. This causes the compression context to be finalized prematurely, resulting in an error when `ZSTD_endStream` is called.

The corrected code uses `ZSTD_e_continue` in the inner loop, which allows the compression context to be used for multiple input buffers. The compression context is then finalized by calling `ZSTD_endStream` after all input buffers have been processed.