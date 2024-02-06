#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "snappy.h"
#include "snappy-internal.h"
#include "snappy-sinksource.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract compressed_len and uncompressed_len from the input data
  if (stream.remaining_bytes() < 2 * sizeof(int)) {
    return 0;
  }
  int compressed_len = stream.ConsumeIntegral<int>();
  int uncompressed_len = stream.ConsumeIntegral<int>();

  // The remaining data is used as input to the decompressor
  std::vector<uint8_t> input_data = stream.ConsumeRemainingBytes<uint8_t>();
  snappy::ByteArraySource source(reinterpret_cast<const char*>(input_data.data()), input_data.size());

  snappy::SnappyDecompressor decompressor(&source, compressed_len, uncompressed_len);
  snappy::SnappySinkAllocator allocator;
  snappy::SnappyScatteredWriter writer(&allocator);

  bool result = snappy::InternalUncompressAllTags<snappy::SnappyScatteredWriter<snappy::SnappySinkAllocator>>(&decompressor, &writer, compressed_len, uncompressed_len);

  return 0;
}