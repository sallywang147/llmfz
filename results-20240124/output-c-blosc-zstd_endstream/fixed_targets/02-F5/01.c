#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzing.h"
#include "zstd.h"

extern "C" {
#include "zstd_errors.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (!cctx) {
    return 0;
  }

  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {NULL, ZSTD_compressBound(size), 0};

  size_t ret = ZSTD_compressStream(cctx, &output, &input);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ret = ZSTD_endStream(cctx, &input);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_freeCCtx(cctx);
  return output.pos;
}