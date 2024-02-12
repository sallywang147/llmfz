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
  struct b2nd_array_t *array = NULL;
  char *key = NULL;
  char value = 0;
  size_t key_len = 0;

  if (size < 1) {
    return 0;
  }

  b2nd_init();

  array = b2nd_new();
  if (array == NULL) {
    b2nd_destroy();
    return 0;
  }

  key_len = data[0] % 1024;
  if (key_len > 0) {
    key = (char *)malloc(key_len + 1);
    if (key == NULL) {
      b2nd_destroy();
      return 0;
    }
    memcpy(key, data + 1, key_len);
    key[key_len] = '\0';
  }

  value = data[key_len + 1];

  b2nd_insert(array, key, key_len, value, size - key_len - 2);

  b2nd_free(array);
  free(key);

  b2nd_destroy();
  return 0;
}

#ifdef __cplusplus
}
#endif