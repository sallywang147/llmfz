#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  std::vector<uint8_t> input_buffer = stream.ConsumeRemainingBytes<uint8_t>();
  ZSTD_inBuffer inBuffer = {input_buffer.data(), input_buffer.size(), 0};

  ZSTD_endStream(cctx, &inBuffer);

  ZSTD_freeCCtx(cctx);
  return 0;
}