#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "iter/impl/Compressed.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create two vectors for the Compressed iterator.
  std::vector<int> int_vector;
  std::vector<bool> bool_vector;

  // Fill the vectors with data from the fuzzer.
  while (stream.remaining_bytes() > 0) {
    int_vector.push_back(stream.ConsumeIntegral<int>());
    bool_vector.push_back(stream.ConsumeBool());
  }

  // Create a Compressed iterator for the two vectors.
  iter::impl::Compressed<std::vector<int>&, std::vector<bool>&> compressed(int_vector, bool_vector);

  // Create an Iterator for the Compressed object.
  auto it = compressed.begin();

  // Call the operator++ function on the Iterator.
  ++it;

  return 0;
}