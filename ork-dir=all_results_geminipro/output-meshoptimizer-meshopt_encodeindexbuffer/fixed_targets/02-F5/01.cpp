#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

void fuzzEncoder(const uint8_t *data, size_t size, size_t stride, int (*encode)(void *, size_t, const int *, size_t)) {
  size_t count = 66; // must be divisible by 3 for encodeIndexBuffer; should be >=64 to cover large vertex blocks

  void *buffer = malloc(count * stride);
  assert(buffer);

  int *indices = reinterpret_cast<int *>(malloc(count * sizeof(int)));
  assert(indices);

  size_t rc = encode(buffer, count * stride, indices, count);
  (void)rc;

  free(buffer);
  free(indices);
}

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // encodeIndexBuffer supports 2 and 4-byte indices
  fuzzEncoder(data, size, 2, meshopt_encodeIndexBuffer);
  fuzzEncoder(data, size, 4, meshopt_encodeIndexBuffer);

  // encodeIndexSequence supports 2 and 4-byte indices
  fuzzEncoder(data, size, 2, meshopt_encodeIndexSequence);
  fuzzEncoder(data, size, 4, meshopt_encodeIndexSequence);

  // encodeVertexBuffer supports any strides divisible by 4 in 4-256 interval
  // It's a waste of time to check all of them, so we'll just check a few with different alignment mod 16
  fuzzEncoder(data, size, 4, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 16, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 24, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 32, meshopt_encodeVertexBuffer);

  return 0;
}
}