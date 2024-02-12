#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "b2nd.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int ret;
  struct b2nd_context_s *ctx = b2nd_init();
  if (!ctx) {
    return 0;
  }

  // get_slice requires a b2nd_array_t.161 as the second argument, which is a
  // pointer to a pointer to a b2nd_array_t.
  struct b2nd_array_t.161 **array_ptr =
      (struct b2nd_array_t.161 **)malloc(sizeof(struct b2nd_array_t.161 *));
  if (!array_ptr) {
    b2nd_destroy(ctx);
    return 0;
  }

  // get_slice requires a b2nd_array_t as the third argument.
  struct b2nd_array_t array;
  memset(&array, 0, sizeof(array));

  // get_slice requires a size_t as the fourth argument.
  size_t offset = stream.ConsumeIntegral<size_t>();

  // get_slice requires a size_t as the fifth argument.
  size_t length = stream.ConsumeIntegral<size_t>();

  // Call the function.
  ret = b2nd_get_slice(ctx, array_ptr, &array, &offset, &length);
  if (ret != 0) {
    // An error occurred.
    b2nd_destroy(ctx);
    free(array_ptr);
    return 0;
  }

  // Clean up.
  b2nd_destroy(ctx);
  free(array_ptr);

  return 0;
}