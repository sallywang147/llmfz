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
  ZSTD_inBuffer in_buffer = {data, size, 0};
  ZSTD_outBuffer out_buffer = {nullptr, 0, 0};
  size_t ret;
  do {
    ret = ZSTD_compressStream(cctx, &out_buffer, &in_buffer);
  } while (ret == 0);
  if (ret != ZSTD_error_dstSize_tooSmall) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}