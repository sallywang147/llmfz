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