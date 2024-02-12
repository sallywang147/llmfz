 #include <fuzzer/FuzzedDataProvider.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct b2nd_context_s* b2nd_context = b2nd_create_context();
  if (b2nd_context == NULL) {
    return 0;
  }

  struct b2nd_array_t* b2nd_array = b2nd_create_array(b2nd_context, 1);
  if (b2nd_array == NULL) {
    b2nd_destroy_context(b2nd_context);
    return 0;
  }

  size_t slice_size = 0;
  size_t slice_offset = 0;
  struct b2nd_array_t* slice_array = NULL;

  int ret = b2nd_get_slice(b2nd_context, &slice_array, b2nd_array, &slice_size, &slice_offset);
  if (ret != 0) {
    b2nd_destroy_array(b2nd_array);
    b2nd_destroy_context(b2nd_context);
    return 0;
  }

  b2nd_destroy_array(slice_array);
  b2nd_destroy_array(b2nd_array);
  b2nd_destroy_context(b2nd_context);

  return 0;
}