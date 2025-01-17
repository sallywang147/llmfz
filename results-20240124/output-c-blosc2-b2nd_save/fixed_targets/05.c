#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <b2nd.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array = b2nd_array_new(1024);
  if (array == NULL) {
    return 0;
  }

  if (size > 0) {
    b2nd_array_set_data(array, (uint8_t *)data, size);
  }

  char *filename = (char *)malloc(size+1);
  if (filename != NULL) {
    memcpy(filename, data, size);
    filename[size] = '\0';

    int ret = b2nd_save(array, filename);
    if (ret != 0) {
      printf("Error saving file: %s\n", filename);
    }

    free(filename);
  }

  b2nd_array_free(array);

  return 0;
}

#ifdef __cplusplus
}
#endif