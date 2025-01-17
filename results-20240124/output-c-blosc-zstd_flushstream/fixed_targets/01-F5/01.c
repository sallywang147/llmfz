#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <zstd.h>

extern "C" {
#include <zstd.h>
}

size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t compressed_size = fdp.ConsumeIntegral<size_t>();
  size_t max_compressed_size = fdp.ConsumeIntegral<size_t>();
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {NULL, compressed_size, 0};
  ZSTD_compressStream(cctx, &output, &input);
  ZSTD_flushStream(cctx, &output);
  ZSTD_freeCCtx(cctx);
  return 0;
}