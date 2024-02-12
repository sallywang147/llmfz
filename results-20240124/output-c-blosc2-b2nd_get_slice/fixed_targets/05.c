#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "b2nd.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_context_s *ctx = b2nd_create_context();
  struct b2nd_array_t *array;
  struct b2nd_array_t *slice;
  size_t slice_size, slice_offset;
  if (ctx == NULL) {
    return 0;
  }
  array = b2nd_create_array(ctx, 0, 0, 0, 0, 0, 0);
  if (array == NULL) {
    b2nd_destroy_context(ctx);
    return 0;
  }
  b2nd_get_slice(ctx, &array, &slice, &slice_size, &slice_offset);
  b2nd_destroy_context(ctx);
  return 0;
}
}