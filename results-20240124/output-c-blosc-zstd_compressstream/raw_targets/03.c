 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  ZSTD_inBuffer input = { nullptr, 0, 0 };
  ZSTD_inBuffer output = { nullptr, 0, 0 };
  ZSTD_compressStream(cctx, &input, &output);
  ZSTD_freeCCtx(cctx);
  return 0;
}