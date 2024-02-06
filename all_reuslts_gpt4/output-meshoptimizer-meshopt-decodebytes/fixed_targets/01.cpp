#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume half of the input data for the data to be decoded
  size_t data_size = stream.remaining_bytes() / 2;
  std::string data_to_decode = stream.ConsumeBytesAsString(data_size);

  // Consume the rest of the input data for the buffer
  size_t buffer_size = stream.remaining_bytes();
  std::vector<char> buffer(buffer_size);

  // Call the function under test
  meshopt::decodeBytes(data_to_decode.data(), data_to_decode.data() + data_to_decode.size(), buffer.data(), buffer_size);

  return 0;
}