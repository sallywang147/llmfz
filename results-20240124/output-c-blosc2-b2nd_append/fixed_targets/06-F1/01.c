#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "b2nd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }
  // Create a B2ND array
  struct b2nd_array_t *array = b2nd_array_create(10);
  if (!array) {
    return 0;
  }

  // Append data to the array
  int ret = b2nd_append(array, (char *)data, size, data[0]);
  if (ret != 0) {
    b2nd_array_destroy(array);
    return 0;
  }

  // Destroy the array
  b2nd_array_destroy(array);
  return 0;
}