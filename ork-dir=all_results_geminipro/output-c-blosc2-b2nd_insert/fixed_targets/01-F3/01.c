#include <fuzzer/FuzzedDataProvider.h>

#include <stdint.h>
#include <stdlib.h>

#include "b2nd_array.h"

extern "C" {
#include "b2nd_array.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize B2ND array.
  struct b2nd_array_t *array = b2nd_array_new();
  if (array == NULL) {
    return 0;
  }

  // Generate random values for function parameters.
  size_t key_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char *key = (char *)malloc(key_size + 1);
  stream.ConsumeBytes(key, key_size);
  key[key_size] = '\0';

  size_t value_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char *value = (char *)malloc(value_size + 1);
  stream.ConsumeBytes(value, value_size);
  value[value_size] = '\0';

  char delimiter = stream.ConsumeIntegral<char>();

  size_t max_value_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);

  // Call the function under test.
  int result = b2nd_insert(array, key, key_size, value, value_size, delimiter, max_value_size);

  // Free allocated memory.
  free(key);
  free(value);
  b2nd_array_free(array);

  return result;
}