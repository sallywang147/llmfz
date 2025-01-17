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
  struct b2nd_array_t *array = b2nd_array_new(10000);
  if (array == NULL) {
    return 0;
  }
  int i = 0, n = 0;
  char *str;
  size_t str_size = 0;
  char c = 0;
  if (size > 0) {
    /* Variable size string */
    str_size = data[0] % 1000;
  }
  if (size > 1) {
    /* Variable character */
    c = data[1];
  }
  if (size > 2) {
    /* Variable number of strings */
    n = data[2] % 100;
  }
  for (i = 0; i < n; i++) {
    str = (char *)malloc(str_size + 1);
    if (str == NULL) {
      b2nd_array_free(array);
      return 0;
    }
    memset(str, c, str_size);
    str[str_size] = '\0';
    b2nd_append(array, str, str_size, c);
    free(str);
  }
  b2nd_array_free(array);
  return 0;
}

#ifdef __cplusplus
}
#endif