 #include <fuzzer/FuzzedDataProvider.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "b2nd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct b2nd_array_t *array = b2nd_array_create();
  if (array == NULL) {
    return 0;
  }

  // Generate a random string to append to the array.
  size_t string_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  char *string = stream.ConsumeBytes<char>(string_size);

  // Generate a random character to use as the separator.
  char separator = stream.ConsumeIntegral<char>();

  // Append the string to the array.
  int result = b2nd_append(array, string, string_size, separator);
  if (result != 0) {
    b2nd_array_destroy(array);
    return 0;
  }

  // Free the memory allocated for the string.
  free(string);

  // Destroy the array.
  b2nd_array_destroy(array);

  return 0;
}