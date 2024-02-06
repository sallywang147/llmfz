#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "iter/impl/Compressed.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::vector<int> intVector;
  std::vector<bool> boolVector;
  iter::impl::Compressed<std::vector<int>, std::vector<bool>> compressed(intVector, boolVector);

  // Initialize the Iterator
  auto iterator = compressed.begin();

  // Use the data provider to decide how many times to increment the iterator
  auto numIncrements = stream.ConsumeIntegralInRange<size_t>(0, size);

  for (size_t i = 0; i < numIncrements; ++i) {
    if (iterator == compressed.end()) {
      break;
    }
    iterator.increment_iterators(&iterator);
  }

  return 0;
}