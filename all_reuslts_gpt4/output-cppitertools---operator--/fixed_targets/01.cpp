#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "iter/impl/compressed.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data to initialize vectors
  size_t vector_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<int> int_vector;
  std::vector<bool> bool_vector;

  for (size_t i = 0; i < vector_size; ++i) {
    int_vector.push_back(stream.ConsumeIntegral<int>());
    bool_vector.push_back(stream.ConsumeBool());
  }

  // Create Compressed object
  iter::impl::Compressed<std::vector<int>&, std::vector<bool>&> compressed(int_vector, bool_vector);

  // Create an Iterator and call operator++
  auto it = compressed.begin();
  while (it != compressed.end()) {
    ++it;
  }

  return 0;
}