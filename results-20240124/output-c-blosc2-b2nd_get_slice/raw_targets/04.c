 #include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include <b2nd.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_context_s *ctx = b2nd_init();
  if (ctx == NULL) {
    return 0;
  }

  struct b2nd_array_t.161 *arr = NULL;
  struct b2nd_array_t arr2 = {0};
  size_t n_slices = 0;
  size_t slice_size = 0;
  int ret = b2nd_get_slice(ctx, &arr, &arr2, &n_slices, &slice_size);
  if (ret != 0) {
    b2nd_destroy(ctx);
    return 0;
  }

  b2nd_destroy(ctx);
  return 0;
}

#ifdef __cplusplus
}
#endif