#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data to create indices
  std::vector<int> indices = stream.ConsumeIntegralVector<int>(stream.remaining_bytes() / sizeof(int));

  // Ensure we have at least one index to prevent division by zero errors
  if(indices.empty()) {
    indices.push_back(0);
  }

  // Calculate the buffer size
  size_t buffer_size = indices.size() * 4;

  // Create the buffer
  std::vector<char> buffer(buffer_size);

  // Call the function to fuzz
  meshopt_encodeIndexBuffer(buffer.data(), buffer_size, indices.data(), indices.size());

  return 0;
}