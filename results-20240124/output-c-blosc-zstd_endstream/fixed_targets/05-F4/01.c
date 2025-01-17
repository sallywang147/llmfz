#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zstd.h>

extern "C" {
#include "fuzzer.h"
}

size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {NULL, 0, 0};

  while (input.pos < input.size) {
    size_t ret = ZSTD_compressStream(cctx, &output, &input);
    if (ZSTD_isError(ret)) {
      fprintf(stderr, "ZSTD_compressStream: %s\n", ZSTD_getErrorName(ret));
      return 0;
    }
  }

  size_t ret = ZSTD_endStream(cctx, &output);
  if (ZSTD_isError(ret)) {
    fprintf(stderr, "ZSTD_endStream: %s\n", ZSTD_getErrorName(ret));
    return 0;
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}