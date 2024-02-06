#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

void fuzzEncoder(const uint8_t *data, size_t size, size_t stride, int (*encode)(void *, size_t, const void *, size_t, size_t)) {
  size_t count = 66; // must be divisible by 3 for decodeIndexBuffer; should be >=64 to cover large vertex blocks

  void *vertices = malloc(count * stride);
  assert(vertices);

  size_t buffer_size = 1024;
  void *buffer = malloc(buffer_size);
  assert(buffer);

  size_t result = encode(buffer, buffer_size, vertices, count, stride);

  free(buffer);
  free(vertices);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // encodeVertexBuffer supports any strides divisible by 4 in 4-256 interval
  // It's a waste of time to check all of them, so we'll just check a few with different alignment mod 16
  fuzzEncoder(data, size, 4, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 16, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 24, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 32, meshopt_encodeVertexBuffer);

  return 0;
}