 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  ZSTD_CCtx_reset(cctx, 0);

  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> input_buffer(provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes()));
  auto input_data = provider.ConsumeBytes<unsigned char>(input_buffer.size());
  ZSTD_inBuffer input = {input_data.data(), input_data.size(), 0};

  ZSTD_endStream(cctx, &input);

  ZSTD_freeCCtx(cctx);

  return 0;
}