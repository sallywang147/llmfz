#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  b2nd_context_s* context = b2nd_new_context();
  if (context == nullptr) {
    return 0;
  }
  b2nd_array_t* array = b2nd_create_array(context, 1, 1, 1, B2ND_TYPE_INT32);
  if (array == nullptr) {
    b2nd_free_context(context);
    return 0;
  }
  size_t offset = stream.ConsumeIntegral<size_t>();
  size_t length = stream.ConsumeIntegral<size_t>();
  int result = b2nd_get_slice(context, array, nullptr, &offset, &length);  // Fix: Pass the correct arguments to b2nd_get_slice
  if (result != 0) {
    b2nd_free_array(array);
    b2nd_free_context(context);
    return 0;
  }
  b2nd_free_array(array);
  b2nd_free_context(context);
  return 0;
}