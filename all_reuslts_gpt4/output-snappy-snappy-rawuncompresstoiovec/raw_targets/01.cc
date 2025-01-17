#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "snappy.h"
#include "snappy-sinksource.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume a portion of the data as the compressed input
  size_t compressed_length = fuzzed_data.ConsumeIntegralInRange<size_t>(0, size);
  std::string compressed = fuzzed_data.ConsumeBytesAsString(compressed_length);

  // Consume the remaining data as the IOVec data blocks
  std::vector<snappy::SnappySinkAllocator::Datablock> iov;
  while (fuzzed_data.remaining_bytes() > 0) {
    size_t block_size = fuzzed_data.ConsumeIntegralInRange<size_t>(0, fuzzed_data.remaining_bytes());
    std::string block_data = fuzzed_data.ConsumeBytesAsString(block_size);
    iov.push_back({block_data.data(), block_size});
  }

  // Call the function under test
  snappy::RawUncompressToIOVec(compressed.data(), compressed.size(), iov.data(), iov.size());

  return 0;
}