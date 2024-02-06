#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct b2nd_context_s context;
  struct b2nd_array_t array;
  struct b2nd_array_t.161 *array161 = nullptr;

  // Initialize context and array with data from the fuzzer
  if (stream.remaining_bytes() < sizeof(context) + sizeof(array)) {
    return 0;
  }
  stream.ConsumeData(&context, sizeof(context));
  stream.ConsumeData(&array, sizeof(array));

  int result = b2nd_copy(&context, &array, &array161);

  // Free the allocated memory
  if (array161 != nullptr) {
    b2nd_free(array161);
  }

  return 0;
}