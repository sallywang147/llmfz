#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

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
  ZSTD_inBuffer input = {nullptr, 0, 0};
  ZSTD_outBuffer output = {nullptr, 0, 0};
  size_t ret;
  do {
    if (provider.remaining_bytes() == 0) {
      break;
    }
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
    input.src = next_input.data();
    input.size = next_input.size();
    input.pos = 0;
    output.dst = new uint8_t[next_input.size() * 2];
    output.size = next_input.size() * 2;
    output.pos = 0;
    ret = ZSTD_compressStream(cctx, &output, &input);
    delete[] output.dst;
  } while (ret == 0);
  ZSTD_freeCCtx(cctx);
  return 0;
}