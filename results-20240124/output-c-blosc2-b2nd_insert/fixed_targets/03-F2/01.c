#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "b2nd.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array;

  array = b2nd_create(10, 10);
  if (!array) {
    return 0;
  }

  for (size_t i = 0; i < size; i++) {
    char *key = (char *)data + i;
    size_t key_len = data[i];
    char value = data[i + key_len + 1];
    size_t value_len = data[i + key_len + 2];

    b2nd_insert(array, key, key_len, value, value_len);
  }

  b2nd_destroy(array);
  return 0;
}
}