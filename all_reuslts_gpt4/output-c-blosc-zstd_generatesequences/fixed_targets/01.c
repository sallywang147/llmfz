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

  // Initialize ZSTD context
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  // Initialize LZ4HC optimal context
  LZ4HC_optimal_t lz4hc_optimal;
  
  // Consume data for LZ4HC_optimal_t
  lz4hc_optimal.price = stream.ConsumeIntegral<int>();
  lz4hc_optimal.off = stream.ConsumeIntegral<int>();
  lz4hc_optimal.mlen = stream.ConsumeIntegral<int>();
  lz4hc_optimal.litlen = stream.ConsumeIntegral<int>();

  // Consume data for sequence size
  size_t sequenceSize = stream.ConsumeIntegral<size_t>();

  // Consume data for output buffer
  size_t outputBufferSize = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<char> outputBuffer(outputBufferSize);

  // Call the target function
  ZSTD_generateSequences(cctx, &lz4hc_optimal, sequenceSize, outputBuffer.data(), outputBufferSize);

  // Clean up
  ZSTD_freeCCtx(cctx);

  return 0;
}