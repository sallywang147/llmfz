#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <b2nd.h>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array = b2nd_array_new(100);
  if (array == NULL) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  size_t key_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char *key = (char *)malloc(key_size + 1);
  if (key == NULL) {
    b2nd_array_delete(array);
    return 0;
  }
  stream.ConsumeBytes<char>(key, key_size);
  key[key_size] = '\0';

  size_t value_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char *value = (char *)malloc(value_size + 1);
  if (value == NULL) {
    free(key);
    b2nd_array_delete(array);
    return 0;
  }
  stream.ConsumeBytes<char>(value, value_size);
  value[value_size] = '\0';

  int result = b2nd_insert(array, key, key_size, value, value_size);
  if (result != 0) {
    printf("Error inserting key-value pair: %d\n", result);
  }

  free(key);
  free(value);
  b2nd_array_delete(array);

  return 0;
}
}