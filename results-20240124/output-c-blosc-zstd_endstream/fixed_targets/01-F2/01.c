#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer input = {nullptr, 0, 0};
  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
    input.src = next_input.data();
    input.size = next_input.size();
    input.pos = 0;
    const size_t ret = ZSTD_compressStream2(cctx, nullptr, 0, &input, nullptr);
    if (ZSTD_isError(ret)) {
      break;
    }
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}