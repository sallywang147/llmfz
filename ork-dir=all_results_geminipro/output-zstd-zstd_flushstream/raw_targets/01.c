#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer input;
  input.src = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(
      0, size));
  input.size = input.src.size();
  input.pos = 0;

  size_t ret = ZSTD_compressStream(cctx, nullptr, 0, &input);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  while (input.pos < input.size) {
    ret = ZSTD_compressStream(cctx, nullptr, 0, &input);
    if (ZSTD_isError(ret)) {
      ZSTD_freeCCtx(cctx);
      return 0;
    }
  }

  ret = ZSTD_flushStream(cctx, nullptr);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}