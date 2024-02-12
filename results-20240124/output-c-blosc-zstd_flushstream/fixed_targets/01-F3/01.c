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

  while (stream.remaining_bytes() > 0) {
    input.src = stream.ConsumeBytes<void>(stream.remaining_bytes());
    input.size = stream.remaining_bytes();
    input.pos = 0;
    size_t const ret = ZSTD_compressStream(cctx, output.data(), output.size(),
                                           &input, ZSTD_e_continue);
    if (ZSTD_isError(ret)) {
      ZSTD_freeCCtx(cctx);
      return 0;
    }
  }
  size_t const ret = ZSTD_flushStream(cctx, &input);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}