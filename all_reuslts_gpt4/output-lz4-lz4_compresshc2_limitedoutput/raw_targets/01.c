#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "lz4.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int srcSize = stream.remaining_bytes() / 2;
  std::string src = stream.ConsumeBytesAsString(srcSize);
  int maxDstSize = srcSize * 2; // LZ4 compression can increase size in worst case.
  std::vector<char> dst(maxDstSize);
  int cLevel = stream.ConsumeIntegralInRange<int>(1, 12);

  LZ4_compressHC2_limitedOutput(src.data(), dst.data(), srcSize, maxDstSize, cLevel);

  return 0;
}