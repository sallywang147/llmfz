#include <stdint.h>
#include <stdlib.h>

#include <b2nd.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_context_s *ctx = b2nd_new_context();
  if (ctx == NULL) {
    return 0;
  }

  struct b2nd_array_t *arr = b2nd_new_array(ctx);
  if (arr == NULL) {
    b2nd_free_context(ctx);
    return 0;
  }

  struct b2nd_array_t **arr2 = (struct b2nd_array_t **)malloc(sizeof(struct b2nd_array_t *));
  if (arr2 == NULL) {
    b2nd_free_array(arr);
    b2nd_free_context(ctx);
    return 0;
  }

  int ret = b2nd_copy(ctx, arr, arr2);

  b2nd_free_array(arr);
  b2nd_free_context(ctx);
  free(arr2);

  return ret;
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct b2nd_context_s *b2nd_new_context(void) {
  return NULL;
}

struct b2nd_array_t *b2nd_new_array(struct b2nd_context_s *ctx) {
  return NULL;
}

void b2nd_free_array(struct b2nd_array_t *arr) {}

void b2nd_free_context(struct b2nd_context_s *ctx) {}

int b2nd_copy(struct b2nd_context_s *ctx, struct b2nd_array_t *arr, struct b2nd_array_t **arr2) {
  return 0;
}

#ifdef __cplusplus
}
#endif