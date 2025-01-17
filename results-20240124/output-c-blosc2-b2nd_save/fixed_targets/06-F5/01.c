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
  b2nd_array_t *array = b2nd_array_new();
  if (array == NULL) {
    return 0;
  }

  char *filename = (char *)malloc(size + 1);
  if (filename == NULL) {
    b2nd_array_free(array);
    return 0;
  }

  memcpy(filename, data, size);
  filename[size] = '\0';

  int ret = b2nd_save(array, filename);

  free(filename);
  b2nd_array_free(array);

  return ret;
}

// Add the following line to link with the b2nd library
#ifdef __cplusplus
}
#endif

extern "C" {
#include <b2nd.h>
}

#ifdef __cplusplus
}
#endif