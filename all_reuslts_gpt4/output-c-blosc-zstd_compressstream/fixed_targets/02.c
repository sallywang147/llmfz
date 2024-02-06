#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize compression context
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (!cctx) {
    return 0;
  }

  // Create input and output buffers
  ZSTD_inBuffer input;
  ZSTD_outBuffer output;

  // Consume data for input buffer
  size_t inputSize = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::vector<uint8_t> inputData = stream.ConsumeBytes<uint8_t>(inputSize);
  input.src = inputData.data();
  input.size = inputData.size();
  input.pos = 0;

  // Consume data for output buffer
  size_t outputSize = stream.ConsumeIntegralInRange<size_t>(0, size - inputSize);
  std::vector<uint8_t> outputData(outputSize);
  output.dst = outputData.data();
  output.size = outputData.size();
  output.pos = 0;

  // Call the target function
  ZSTD_compressStream(cctx, &output, &input);

  // Clean up
  ZSTD_freeCCtx(cctx);

  return 0;
}