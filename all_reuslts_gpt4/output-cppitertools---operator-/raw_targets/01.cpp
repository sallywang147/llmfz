#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "iter/impl/compressed.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<int> int_vector;
  std::vector<bool> bool_vector;

  while (stream.remaining_bytes() > 0) {
    int_vector.push_back(stream.ConsumeIntegral<int>());
    bool_vector.push_back(stream.ConsumeBool());
  }

  iter::impl::Compressed<std::vector<int>, std::vector<bool>> compressed(int_vector, bool_vector);

  auto it = compressed.begin();
  while (it != compressed.end()) {
    int *value = *it;
    if (value != nullptr) {
      // Use the value in some way
    }
    ++it;
  }

  return 0;
}