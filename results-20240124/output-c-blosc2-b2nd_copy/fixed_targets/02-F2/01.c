#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "b2nd.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int ret;
  struct b2nd_context_s *ctx = b2nd_init();
  struct b2nd_array_t *arr = b2nd_array_create(ctx, 1, 1, 1);
  struct b2nd_array_t *arr_copy = NULL;

  ret = b2nd_copy(ctx, arr, &arr_copy);

  b2nd_array_destroy(arr);
  b2nd_array_destroy(arr_copy);
  b2nd_destroy(ctx);

  return 0;
}

#ifdef __cplusplus
}
#endif

extern "C" {
struct b2nd_context_s *b2nd_init(void);
struct b2nd_array_t *b2nd_array_create(struct b2nd_context_s *ctx, uint32_t width, uint32_t height, uint32_t channels);
void b2nd_array_destroy(struct b2nd_array_t *arr);
void b2nd_destroy(struct b2nd_context_s *ctx);
int b2nd_copy(struct b2nd_context_s *ctx, struct b2nd_array_t *arr, struct b2nd_array_t **arr_copy);
}