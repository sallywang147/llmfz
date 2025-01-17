#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "b2nd.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array = b2nd_array_new(1024, 1024);
  if (array == NULL) {
    return 0;
  }

  int ret = b2nd_save(array, (char *)data);
  b2nd_array_free(array);
  return ret;
}

#ifdef __cplusplus
}
#endif

// b2nd.h
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct b2nd_array_t {
  uint32_t width;
  uint32_t height;
  uint8_t *data;
};

struct b2nd_array_t *b2nd_array_new(uint32_t width, uint32_t height) {
  struct b2nd_array_t *array = (struct b2nd_array_t *)malloc(sizeof(struct b2nd_array_t));
  if (array == NULL) {
    return NULL;
  }

  array->width = width;
  array->height = height;
  array->data = (uint8_t *)malloc(width * height);
  if (array->data == NULL) {
    free(array);
    return NULL;
  }

  return array;
}

void b2nd_array_free(struct b2nd_array_t *array) {
  if (array == NULL) {
    return;
  }

  free(array->data);
  free(array);
}

int b2nd_save(struct b2nd_array_t *array, char *data) {
  if (array == NULL || data == NULL) {
    return -1;
  }

  memcpy(array->data, data, array->width * array->height);
  return 0;
}

#ifdef __cplusplus
}
#endif