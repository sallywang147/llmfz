#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <b2nd.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array = b2nd_array_new(1, 1, 1);
  char *filename = (char *)malloc(size + 1);
  memcpy(filename, data, size);
  filename[size] = '\0';

  int ret = b2nd_save(array, filename);

  b2nd_array_free(array);
  free(filename);

  return ret;
}

#ifdef __cplusplus
}
#endif

int main() {
  return 0;
}