#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize a b2nd_array_t object
  struct b2nd_array_t array;
  array.size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  array.data = (int *)malloc(array.size * sizeof(int));
  for (size_t i = 0; i < array.size; i++) {
    array.data[i] = stream.ConsumeIntegral<int>();
  }

  // Define and initialize a file name
  std::string filename = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 15));
  filename += ".b2nd";

  // Call the function to fuzz
  b2nd_save(&array, const_cast<char*>(filename.c_str()));

  // Cleanup
  free(array.data);

  return 0;
}