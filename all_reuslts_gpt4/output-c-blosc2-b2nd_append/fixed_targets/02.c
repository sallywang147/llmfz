#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "b2nd_array.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize a b2nd_array_t object
  struct b2nd_array_t array;
  b2nd_array_init(&array);

  // Consume a string from the data
  std::string str = stream.ConsumeRandomLengthString();
  char* str_ptr = const_cast<char*>(str.c_str());

  // Consume a size from the data
  size_t str_size = stream.ConsumeIntegralInRange<size_t>(0, str.size());

  // Consume a character from the data
  char ch = stream.ConsumeIntegral<char>();

  // Call the function to fuzz
  b2nd_append(&array, str_ptr, str_size, ch);

  // Clean up
  b2nd_array_free(&array);

  return 0;
}