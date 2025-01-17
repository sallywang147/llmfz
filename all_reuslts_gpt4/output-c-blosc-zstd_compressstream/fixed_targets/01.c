#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  size_t const bufferSize = ZSTD_CStreamOutSize();
  void* buffer = malloc(bufferSize);
  if (buffer == nullptr) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {buffer, bufferSize, 0};

  while (input.pos < input.size) {
    size_t const ret = ZSTD_compressStream(cctx, &output, &input);
    if (ZSTD_isError(ret)) {
      break;
    }
    if (output.pos == output.size) {
      output.pos = 0;
    }
  }

  ZSTD_endStream(cctx, &output);
  ZSTD_freeCCtx(cctx);
  free(buffer);

  return 0;
}