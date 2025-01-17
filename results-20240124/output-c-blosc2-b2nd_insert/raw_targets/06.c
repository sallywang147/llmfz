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
  struct b2nd_array_t *array = b2nd_array_new(1024, 1024);
  if (array == NULL) {
    return 0;
  }

  for (size_t i = 0; i < size; i++) {
    char key[1024];
    size_t key_len = data[i] % (ARRAY_SIZE(key) - 1) + 1;
    memcpy(key, data + i + 1, key_len);
    char value = data[i + 1 + key_len];
    size_t value_len = data[i + 2 + key_len] % (ARRAY_SIZE(key) - 1) + 1;
    memcpy(key, data + i + 3 + key_len, value_len);

    int ret = b2nd_insert(array, key, key_len, value, value_len);
    if (ret != 0) {
      printf("Error inserting key/value pair: %d\n", ret);
    }
  }

  b2nd_array_free(array);

  return 0;
}

#ifdef __cplusplus
}
#endif