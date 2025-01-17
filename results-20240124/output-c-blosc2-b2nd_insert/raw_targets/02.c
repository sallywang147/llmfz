 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <b2nd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct b2nd_array_t *array = b2nd_array_new();
  if (!array) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  int key_size = stream.ConsumeIntegral<int>();
  if (key_size < 0) {
    key_size = -key_size;
  }
  char *key = (char *)malloc(key_size);
  if (!key) {
    b2nd_array_free(array);
    return 0;
  }
  stream.ConsumeBytes<char>(key, key_size);

  int value_size = stream.ConsumeIntegral<int>();
  if (value_size < 0) {
    value_size = -value_size;
  }
  char *value = (char *)malloc(value_size);
  if (!value) {
    free(key);
    b2nd_array_free(array);
    return 0;
  }
  stream.ConsumeBytes<char>(value, value_size);

  b2nd_insert(array, key, key_size, value, value_size);

  free(key);
  free(value);
  b2nd_array_free(array);
  return 0;
}