#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <zstd.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  ZSTD_inBuffer input;
  ZSTD_outBuffer output;

  while (fdp.remaining_bytes() > 0) {
    size_t len = fdp.ConsumeBytes<uint8_t>(fdp.remaining_bytes());
    input.src = fdp.ConsumeBytes<uint8_t>(len);
    input.size = len;
    input.pos = 0;
    output.dst = fdp.ConsumeBytes<uint8_t>(fdp.remaining_bytes());
    output.size = fdp.remaining_bytes();
    output.pos = 0;

    size_t compressed_size = ZSTD_compressStream(cctx, &output, &input);
    if (ZSTD_isError(compressed_size)) {
      break;
    }

    // Flush the remaining data in the internal buffer of the compressor.
    size_t remaining_size = ZSTD_flushStream(cctx, &input);
    if (ZSTD_isError(remaining_size)) {
      break;
    }
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}