#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <vector>

#include "iter/impl/Compressed.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create the vectors for Compressed
  std::vector<int> int_vector = stream.ConsumeIntegralVector<int>();
  std::vector<bool> bool_vector = stream.ConsumeBoolVector();

  // Create the Compressed object
  iter::impl::Compressed<std::vector<int>, std::vector<bool>> compressed(int_vector, bool_vector);

  // Create the Iterator object
  auto iterator = compressed.begin();

  // Call increment_iterators
  iterator.increment_iterators(&iterator);

  return 0;
}