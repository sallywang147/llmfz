#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <zstd.h>

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (!cctx) {
    return 0;
  }
  ZSTD_inBuffer input = {nullptr, 0, 0};
  ZSTD_inBuffer output = {nullptr, 0, 0};
  size_t compressed_size = 0;
  size_t remaining = size;
  size_t offset = 0;
  while (remaining > 0) {
    size_t chunk_size = stream.ConsumeIntegralInRange<size_t>(0, remaining);
    input.src = stream.ConsumeBytes<uint8_t>(chunk_size).data();
    input.size = chunk_size;
    input.pos = 0;
    output.dst = malloc(ZSTD_compressBound(chunk_size));
    if (!output.dst) {
      ZSTD_freeCCtx(cctx);
      return 0;
    }
    output.size = ZSTD_compressBound(chunk_size);
    output.pos = 0;
    compressed_size += ZSTD_compressStream(cctx, &output, &input);
    free(output.dst);
    remaining -= chunk_size;
    offset += chunk_size;
  }
  ZSTD_freeCCtx(cctx);
  return compressed_size;
}