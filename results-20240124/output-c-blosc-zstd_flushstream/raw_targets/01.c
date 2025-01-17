 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer input = {nullptr, 0, 0};
  std::vector<uint8_t> output(ZSTD_compressBound(size));

  size_t const ret = ZSTD_compressStream(cctx, output.data(), output.size(),
                                         &input, ZSTD_e_end);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}