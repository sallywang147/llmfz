#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>

#include "snappy.h"
#include "snappy-sinksource.h"
#include "snappy-c.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t compressed_len = stream.ConsumeIntegralInRange<int>(0, size / 2);
  size_t uncompressed_len = stream.ConsumeIntegralInRange<int>(0, size / 2);

  std::string input1 = stream.ConsumeBytesAsString(compressed_len);
  std::string input2 = stream.ConsumeBytesAsString(uncompressed_len);

  snappy::SnappyDecompressor decompressor(input1.data(), input1.size());
  snappy::SnappySinkAllocator allocator;
  snappy::SnappyScatteredWriter writer(allocator, input2.data(), input2.size(), 1);

  snappy::InternalUncompressAllTags<snappy::SnappyScatteredWriter<snappy::SnappySinkAllocator>>(&decompressor, &writer, compressed_len, uncompressed_len);

  return 0;
}