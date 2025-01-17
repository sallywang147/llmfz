#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "b2nd.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array = b2nd_array_new(1024);
  if (array == NULL) {
    return 0;
  }
  const char *const separators[] = {",", ";", ":", "|", "\t", " ", "\n"};
  char *sep = separators[data[0] % ARRAY_SIZE(separators)];
  char *str = (char *)malloc(size + 1);
  if (str == NULL) {
    b2nd_array_free(array);
    return 0;
  }
  memcpy(str, data, size);
  str[size] = '\0';
  int ret = b2nd_append(array, str, size, *sep);
  free(str);
  b2nd_array_free(array);
  return ret;
}

#ifdef __cplusplus
}
#endif