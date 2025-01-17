#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer input = {nullptr, 0, 0};
  ZSTD_outBuffer output = {nullptr, 0, 0};

  size_t compressed_size = 0;
  size_t input_size = 0;
  while (provider.remaining_bytes() > 0) {
    if (input_size == 0) {
      input_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
      input.src = provider.ConsumeBytes<unsigned char>(input_size).data();
      input.size = input_size;
    }

    compressed_size = ZSTD_compressStream(cctx, &output, &input);
    if (ZSTD_isError(compressed_size)) {
      ZSTD_freeCCtx(cctx);
      return 0;
    }

    output.src = nullptr;
    output.size = 0;
    input_size = 0;
  }

  ZSTD_freeCCtx(cctx);

  return 0;
}