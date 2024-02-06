#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the b2nd_context_s structure
  struct b2nd_context_s context;
  
  // Initialize the b2nd_array_t.161 structure
  struct b2nd_array_t.161 array_161;

  // Initialize the b2nd_array_t structure
  struct b2nd_array_t array;

  // Initialize pointers to size_t variables
  size_t size1 = stream.ConsumeIntegral<size_t>();
  size_t size2 = stream.ConsumeIntegral<size_t>();

  // Call the function under test
  b2nd_get_slice(&context, &array_161, &array, &size1, &size2);

  return 0;
}