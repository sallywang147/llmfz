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
  if (!cctx) {
    return 0;
  }

  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {NULL, 0, 0};

  size_t ret;
  do {
    ret = ZSTD_compressStream(cctx, &output, &input);
  } while (ret == ZSTD_OK);

  if (ret == ZSTD_error_dstSize_tooSmall) {
    output.dstCapacity = output.pos + ZSTD_compressBound(input.size);
    output.dst = (uint8_t *)malloc(output.dstCapacity);
    ret = ZSTD_compressStream(cctx, &output, &input);
  }

  // Add a call to ZSTD_flushStream to flush any remaining data in the compressor.
  ZSTD_flushStream(cctx, &input);

  ZSTD_freeCCtx(cctx);
  free(output.dst);

  if (ret != ZSTD_OK) {
    return 0;
  }

  return size;
}