#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a ZSTD compression context
  ZSTD_CCtx *cctx = ZSTD_createCCtx();
  if (cctx == NULL) {
    return 0;
  }

  // Prepare input data
  size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const void *input = stream.ConsumeBytes<uint8_t>(input_size).data();

  // Prepare output buffer
  size_t output_size = ZSTD_CStreamOutSize();
  void *output = malloc(output_size);

  // Prepare inBuffer
  ZSTD_inBuffer inBuffer;
  inBuffer.src = input;
  inBuffer.size = input_size;
  inBuffer.pos = 0;

  // Compress the data
  ZSTD_compressStream2(cctx, &inBuffer, NULL, ZSTD_e_continue);

  // Flush the stream
  ZSTD_flushStream(cctx, &inBuffer);

  // Clean up
  free(output);
  ZSTD_freeCCtx(cctx);

  return 0;
}