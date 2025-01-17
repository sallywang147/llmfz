#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <b2nd.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array = b2nd_array_new(100, 100, 100, 100);
  if (array == NULL) {
    return 0;
  }

  int ret = b2nd_save(array, (char *)data);
  if (ret != 0) {
    printf("b2nd_save failed with error code %d\n", ret);
  }

  b2nd_array_free(array);

  return 0;
}

#ifdef __cplusplus
}
#endif