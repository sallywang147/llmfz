#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "lz4.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  // Divide the data into two parts: one for the source and one for the destination.
  const size_t src_size = fuzzed_data.ConsumeIntegralInRange<size_t>(1, size / 2);
  const size_t max_dst_size = size - src_size;

  std::vector<char> src(src_size);
  std::vector<char> dst(max_dst_size);

  // Fill the source buffer with data.
  const std::vector<uint8_t> src_data = fuzzed_data.ConsumeBytes<uint8_t>(src_size);
  std::copy(src_data.begin(), src_data.end(), src.begin());

  // Choose a compression level between 1 and 12.
  const int cLevel = fuzzed_data.ConsumeIntegralInRange<int>(1, 12);

  // Call the function to be fuzzed.
  LZ4_compressHC2_limitedOutput(src.data(), dst.data(), src_size, max_dst_size, cLevel);

  return 0;
}