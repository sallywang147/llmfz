 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct b2nd_array_t *array = b2nd_create();
  if (array == NULL) {
    return 0;
  }
  size_t key_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char *key = (char *)malloc(key_size);
  if (key == NULL) {
    b2nd_destroy(array);
    return 0;
  }
  stream.ConsumeBytes(key, key_size);
  size_t value_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char *value = (char *)malloc(value_size);
  if (value == NULL) {
    free(key);
    b2nd_destroy(array);
    return 0;
  }
  stream.ConsumeBytes(value, value_size);
  char delimiter = (char)stream.ConsumeIntegral<int>();
  size_t max_num_values = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  int ret = b2nd_insert(array, key, key_size, delimiter, max_num_values);
  if (ret == 0) {
    ret = b2nd_insert(array, value, value_size, delimiter, max_num_values);
  }
  free(key);
  free(value);
  b2nd_destroy(array);
  return 0;
}