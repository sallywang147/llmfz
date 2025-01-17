#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  ZSTD_inBuffer input_buffer;
  input_buffer.src = data;
  input_buffer.size = size;
  input_buffer.pos = 0;
  ZSTD_compressStream(cctx, &input_buffer);
  ZSTD_flushStream(cctx, &input_buffer);
  ZSTD_freeCCtx(cctx);
  return 0;
}