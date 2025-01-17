#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // We need at least one byte for buffer and one int for indices
  if (size < sizeof(int) + 1) {
    return 0;
  }

  // Consume 1 byte for buffer
  std::vector<char> buffer = stream.ConsumeBytes<char>(1);

  // Consume remaining bytes for indices
  std::vector<int> indices = stream.ConsumeRemainingBytes<int>();

  // Call the function to fuzz
  meshopt_encodeIndexBuffer(buffer.data(), buffer.size(), indices.data(), indices.size());

  return 0;
}