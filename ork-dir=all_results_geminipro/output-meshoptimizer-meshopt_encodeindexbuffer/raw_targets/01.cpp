#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

namespace meshopt {
extern unsigned int cpuid;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t count = 66; // must be divisible by 3 for decodeIndexBuffer; should be >=64 to cover large vertex blocks

  int *indices = reinterpret_cast<int *>(malloc(count * sizeof(int)));
  assert(indices);

  size_t buffer_size = 1024;
  char *buffer = reinterpret_cast<char *>(malloc(buffer_size));
  assert(buffer);

  size_t result = meshopt_encodeIndexBuffer(buffer, buffer_size, indices, count);
  (void)result;

  free(buffer);
  free(indices);

  return 0;
}