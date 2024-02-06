#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "b2nd_array.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct b2nd_array_t array;
  
  // Initializing the array
  b2nd_array_init(&array);
  
  // Extracting data for the function parameters
  size_t str_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string str = stream.ConsumeBytesAsString(str_size);
  char* ptr = const_cast<char*>(str.c_str());
  
  char c = stream.ConsumeIntegral<char>();
  size_t pos = stream.ConsumeIntegralInRange<size_t>(0, str_size);
  
  // Calling the function
  b2nd_insert(&array, ptr, str_size, c, pos);
  
  // Cleaning up
  b2nd_array_free(&array);
  
  return 0;
}