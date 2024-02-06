#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <assert.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t buffer_size = 66; // must be divisible by 3 for decodeIndexBuffer; should be >=64 to cover large vertex blocks

  char *buffer = (char *)malloc(buffer_size);
  assert(buffer);

  meshopt::decodeIndexBuffer(buffer, buffer_size, (uint32_t *)data, size / sizeof(uint32_t));

  meshopt::decodeBytes(buffer, buffer + buffer_size, buffer, buffer_size);

  free(buffer);

  return 0;
}