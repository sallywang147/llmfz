#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  ZSTD_inBuffer inBuffer;
  inBuffer.size = stream.remaining_bytes();
  inBuffer.pos = 0;
  std::vector<uint8_t> inData = stream.ConsumeRemainingBytes<uint8_t>();
  inBuffer.src = inData.data();

  ZSTD_flushStream(cctx, &inBuffer);

  ZSTD_freeCCtx(cctx);

  return 0;
}