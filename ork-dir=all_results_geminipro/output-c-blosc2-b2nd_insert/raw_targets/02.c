#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  b2nd_array_t *array = b2nd_array_new(stream.ConsumeIntegral<size_t>());
  if (!array) {
    return 0;
  }

  size_t key_size = stream.ConsumeIntegral<size_t>();
  char *key = (char *)stream.ConsumeBytes<char>(key_size);
  if (!key) {
    b2nd_array_free(array);
    return 0;
  }

  size_t value_size = stream.ConsumeIntegral<size_t>();
  char *value = (char *)stream.ConsumeBytes<char>(value_size);
  if (!value) {
    free(key);
    b2nd_array_free(array);
    return 0;
  }

  char delim = stream.ConsumeIntegral<char>();

  size_t max_entries = stream.ConsumeIntegral<size_t>();

  b2nd_insert(array, key, key_size, value, value_size, delim, max_entries);

  b2nd_array_free(array);
  free(key);
  free(value);

  return 0;
}