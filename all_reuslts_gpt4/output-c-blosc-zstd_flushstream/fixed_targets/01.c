#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ZSTD_init();
    initialized = true;
  }

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> input_buffer = stream.ConsumeRemainingBytes<uint8_t>();

  ZSTD_inBuffer_s input = {input_buffer.data(), input_buffer.size(), 0};

  ZSTD_flushStream(cctx, &input);

  ZSTD_freeCCtx(cctx);

  return 0;
}