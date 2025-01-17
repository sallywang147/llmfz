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
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {nullptr, 0, 0};

  size_t ret = ZSTD_initCCtx(cctx, 1);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  do {
    ret = ZSTD_compressStream(cctx, &output, &input);
    if (ZSTD_isError(ret)) {
      ZSTD_freeCCtx(cctx);
      return 0;
    }
  } while (input.pos < input.size);

  ret = ZSTD_flushStream(cctx, &output);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_freeCCtx(cctx);

  return 0;
}