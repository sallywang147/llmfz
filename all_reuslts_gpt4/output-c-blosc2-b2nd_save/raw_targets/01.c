#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "b2nd_array.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the array
  struct b2nd_array_t array;
  array.size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  array.data = new int[array.size];
  for (size_t i = 0; i < array.size; i++) {
    array.data[i] = stream.ConsumeIntegral<int>();
  }

  // Define and initialize the filename
  std::string filename = stream.ConsumeRemainingBytesAsString();
  char* filename_cstr = const_cast<char*>(filename.c_str());

  // Call the function to fuzz
  int result = b2nd_save(&array, filename_cstr);

  // Clean up
  delete[] array.data;

  return 0;
}