#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zstd.h"

extern "C" {
#include "fuzz_helpers.h"
}

size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  if (!cctx) {
    /* Handle error */
  }

  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {NULL, ZSTD_COMPRESSBOUND(size), 0};

  while (input.pos < input.size) {
    size_t const ret = ZSTD_compressStream(cctx, &output, &input);
    if (ZSTD_isError(ret)) {
      /* Handle error */
    }
  }

  /* Call ZSTD_endStream to properly end the stream and release resources. */
  size_t const ret = ZSTD_endStream(cctx, &input);
  if (ZSTD_isError(ret)) {
    /* Handle error */
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}