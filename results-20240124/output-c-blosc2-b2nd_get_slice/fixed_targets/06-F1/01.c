#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "b2nd.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

struct b2nd_array_t {
  size_t size;
  uint8_t data[];
};

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_context_s *ctx;
  struct b2nd_array_t *a1, *a2;
  size_t *sz1, *sz2;
  int ret;

  ctx = b2nd_new_context();
  if (ctx == NULL) {
    return 0;
  }

  a1 = malloc(sizeof(struct b2nd_array_t));
  a2 = malloc(sizeof(struct b2nd_array_t));
  sz1 = malloc(sizeof(size_t));
  sz2 = malloc(sizeof(size_t));

  if (a1 == NULL || a2 == NULL || sz1 == NULL || sz2 == NULL) {
    free(ctx);
    return 0;
  }

  ret = b2nd_get_slice(ctx, &a1, a2, sz1, sz2);
  if (ret != 0) {
    free(ctx);
    free(a1);
    free(a2);
    free(sz1);
    free(sz2);
    return 0;
  }

  free(ctx);
  free(a1);
  free(a2);
  free(sz1);
  free(sz2);

  return 0;
}

#ifdef __cplusplus
}
#endif