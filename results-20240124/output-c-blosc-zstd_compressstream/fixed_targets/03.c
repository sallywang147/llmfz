#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "zstd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  ZSTD_inBuffer input = { nullptr, 0, 0 };
  ZSTD_outBuffer output = { nullptr, 0, 0 };
  ZSTD_compressStream(cctx, &output, &input);
  ZSTD_freeCCtx(cctx);
  return 0;
}