#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "b2nd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t array_size = stream.ConsumeIntegral<size_t>();
  const size_t slice_size = stream.ConsumeIntegral<size_t>();
  const size_t slice_offset = stream.ConsumeIntegral<size_t>();
  const size_t slice_stride = stream.ConsumeIntegral<size_t>();
  const size_t slice_count = stream.ConsumeIntegral<size_t>();

  struct b2nd_context_s* context = b2nd_create_context();
  if (context == nullptr) {
    return 0;
  }

  struct b2nd_array_t* array = b2nd_create_array(context, array_size);
  if (array == nullptr) {
    b2nd_destroy_context(context);
    return 0;
  }

  struct b2nd_array_t* slice = nullptr;
  size_t slice_length = 0;
  size_t slice_offset_out = 0;

  int result = b2nd_get_slice(context, &slice, array, &slice_length,
                               &slice_offset_out);
  if (result != 0) {
    b2nd_destroy_array(array);
    b2nd_destroy_context(context);
    return 0;
  }

  b2nd_destroy_slice(slice);  // Destroy the slice before destroying the array and context
  b2nd_destroy_array(array);
  b2nd_destroy_context(context);
  return 0;
}