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

  meshopt::decodeBytes((char *)data, (char *)data + size, buffer, buffer_size);

  free(buffer);

  return 0;
}