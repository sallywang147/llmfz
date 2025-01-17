#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "b2nd_array.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the b2nd_array_t structure
  struct b2nd_array_t array;
  array.size = 0;
  array.capacity = 0;
  array.data = NULL;

  // Consume data from the fuzzer input
  size_t length = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string str = stream.ConsumeBytesAsString(length);
  char delimiter = stream.ConsumeIntegral<char>();

  // Call the target function
  b2nd_append(&array, str.data(), length, delimiter);

  // Free the allocated memory
  free(array.data);

  return 0;
}