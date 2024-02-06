#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t chunk_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::vector<uint8_t> chunk = stream.ConsumeBytes<uint8_t>(chunk_size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer input = {chunk.data(), chunk.size(), 0};
  ZSTD_outBuffer output = {nullptr, 0, 0};

  size_t ret = ZSTD_compressStream(cctx, &output, &input);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ret = ZSTD_flushStream(cctx, &output);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}