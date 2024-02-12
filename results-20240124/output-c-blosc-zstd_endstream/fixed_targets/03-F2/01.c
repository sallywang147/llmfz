#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <zstd.h>

extern "C" {
#include <zstd.h>
}

size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  ZSTD_inBuffer input = {nullptr, 0, 0};
  ZSTD_outBuffer output = {nullptr, 0, 0};
  size_t ret;

  while (fdp.remaining_bytes() > 0) {
    input.src = fdp.ConsumeBytes<void>(fdp.remaining_bytes());
    input.size = fdp.remaining_bytes();
    ret = ZSTD_compressStream(cctx, &output, &input);
    if (ZSTD_isError(ret)) {
      ZSTD_freeCCtx(cctx);
      return 0;
    }
  }

  ZSTD_endStream(cctx, &output);
  ZSTD_freeCCtx(cctx);
  return 0;
}