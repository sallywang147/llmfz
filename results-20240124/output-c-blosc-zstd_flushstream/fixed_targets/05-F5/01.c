#include <stddef.h>
#include <stdint.h>
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
    ZSTD_compressStream(cctx, &output, &input);
  }

  ZSTD_flushStream(cctx, &output);
  ZSTD_freeCCtx(cctx);
  return 0;
}