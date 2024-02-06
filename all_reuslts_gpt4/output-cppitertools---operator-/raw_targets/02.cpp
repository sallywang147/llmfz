#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "iter/impl/compressed.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the vectors
  std::vector<int> intVector;
  std::vector<bool> boolVector;

  // Fill the vectors with fuzzed data
  while (stream.remaining_bytes() > 0) {
    // Consume an integer and a boolean from the fuzzed data
    int intValue = stream.ConsumeIntegral<int>();
    bool boolValue = stream.ConsumeBool();

    // Add the consumed values to the vectors
    intVector.push_back(intValue);
    boolVector.push_back(boolValue);
  }

  // Create a Compressed object
  iter::impl::Compressed<std::vector<int>, std::vector<bool>> compressed(intVector, boolVector);

  // Create an Iterator object
  auto iterator = compressed.begin();

  // Call operator* on the Iterator
  if (iterator != compressed.end()) {
    int* result = *iterator;
  }

  return 0;
}