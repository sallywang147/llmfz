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
  ZSTD_inBuffer input;
  input.src = provider.ConsumeBytes<unsigned char>(size).data();
  input.size = size;
  input.pos = 0;
  size_t result = ZSTD_compressStream(cctx, nullptr, 0, &input);
  if (ZSTD_isError(result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }
  result = ZSTD_flushStream(cctx, &input);
  if (ZSTD_isError(result)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}