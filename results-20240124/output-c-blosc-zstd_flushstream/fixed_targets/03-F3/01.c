#include <zstd.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {NULL, 0, 0};
  size_t ret;

  while ((ret = ZSTD_compressStream(cctx, &output, &input)) > 0) {
    // Do something with the compressed data in output.pos
  }
  ZSTD_flushStream(cctx, &output);

  ZSTD_freeCCtx(cctx);
  return 0;
}