#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zstd.h>

extern "C" {
#include "zstd_errors.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  if (cctx == NULL) {
    return 0;
  }

  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {NULL, 0, 0};

  size_t ret = ZSTD_compressStream(cctx, &output, &input);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_endStream(cctx, &input);
  ZSTD_freeCCtx(cctx);

  return ret;
}