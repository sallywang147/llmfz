#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  size_t const kMaxSequences = 256;
  ZSTD_Sequence sequences[kMaxSequences];

  size_t const numSequences = stream.ConsumeIntegralInRange<size_t>(0, kMaxSequences);
  std::vector<char> source = stream.ConsumeRemainingBytes<char>();

  size_t const result = ZSTD_generateSequences(cctx, sequences, numSequences, source.data(), source.size());

  ZSTD_freeCCtx(cctx);
  
  return 0;
}