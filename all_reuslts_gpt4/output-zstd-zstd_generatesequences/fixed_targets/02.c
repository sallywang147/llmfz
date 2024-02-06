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

  size_t maxSequences = stream.ConsumeIntegral<size_t>();
  std::vector<ZSTD_Sequence> sequences(maxSequences);

  size_t bufferSize = stream.remaining_bytes() / 2;
  std::vector<char> buffer(bufferSize);

  size_t numSequences = ZSTD_generateSequences(cctx, sequences.data(), sequences.size(), buffer.data(), bufferSize);

  ZSTD_freeCCtx(cctx);

  return 0;
}