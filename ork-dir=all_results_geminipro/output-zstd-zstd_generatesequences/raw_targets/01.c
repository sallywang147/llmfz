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
  const size_t num_sequences = stream.ConsumeIntegral<size_t>();
  std::vector<ZSTD_Sequence> sequences(num_sequences);
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> buffer(buffer_size);
  size_t generated = ZSTD_generateSequences(cctx, sequences.data(),
                                            sequences.size(), buffer.data(),
                                            buffer.size());
  ZSTD_freeCCtx(cctx);
  return 0;
}