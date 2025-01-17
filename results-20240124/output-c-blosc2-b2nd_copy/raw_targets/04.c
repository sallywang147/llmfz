 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct b2nd_context_s *ctx = b2nd_new_context();
  if (!ctx)
    return 0;

  struct b2nd_array_t *arr = b2nd_new_array(ctx, 0, 0);
  if (!arr) {
    b2nd_free_context(ctx);
    return 0;
  }

  struct b2nd_array_t **out = (struct b2nd_array_t **)malloc(sizeof(struct b2nd_array_t *));
  if (!out) {
    b2nd_free_array(arr);
    b2nd_free_context(ctx);
    return 0;
  }

  int res = b2nd_copy(ctx, arr, out);
  if (res < 0) {
    free(out);
    b2nd_free_array(arr);
    b2nd_free_context(ctx);
    return 0;
  }

  b2nd_free_array(*out);
  free(out);
  b2nd_free_array(arr);
  b2nd_free_context(ctx);
  return 0;
}