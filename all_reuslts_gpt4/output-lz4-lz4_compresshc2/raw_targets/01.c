#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "lz4.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int srcSize = stream.ConsumeIntegralInRange<int>(0, size);
  std::string src = stream.ConsumeBytesAsString(srcSize);
  const int cLevel = stream.ConsumeIntegralInRange<int>(1, LZ4HC_CLEVEL_MAX);

  // The LZ4_compressBound function provides the maximum size that LZ4 compression may output in a "worst case" scenario
  const int maxDstSize = LZ4_compressBound(srcSize);
  std::vector<char> dst(maxDstSize);

  LZ4_compressHC2(src.data(), dst.data(), srcSize, cLevel);

  return 0;
}