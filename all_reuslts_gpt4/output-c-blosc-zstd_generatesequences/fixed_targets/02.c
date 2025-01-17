#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"
#include "lz4hc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ZSTD_CCtx and LZ4HC_optimal_t
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  LZ4HC_optimal_t lz4hc_optimal;
  memset(&lz4hc_optimal, 0, sizeof(lz4hc_optimal));

  // Get the sequence size
  size_t sequence_size = stream.ConsumeIntegral<size_t>();

  // Generate a string for the sequences
  std::string sequences = stream.ConsumeRemainingBytesAsString();

  // Call ZSTD_generateSequences
  ZSTD_generateSequences(cctx, &lz4hc_optimal, sequence_size, sequences.data(), sequences.size());

  // Clean up
  ZSTD_freeCCtx(cctx);

  return 0;
}