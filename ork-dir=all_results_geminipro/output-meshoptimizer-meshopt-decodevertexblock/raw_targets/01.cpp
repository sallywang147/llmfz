#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const size_t vertex_count = 66; // must be divisible by 3 for decodeIndexBuffer; should be >=64 to cover large vertex blocks
  const size_t vertex_size = 16; // must be divisible by 4

  char *vertex_data = (char *)malloc(vertex_count * vertex_size);
  assert(vertex_data);

  char *last_vertex = vertex_data + (vertex_count - 1) * vertex_size;

  char *rc = meshopt::decodeVertexBlock((char *)data, (char *)data + size, vertex_data, vertex_count, vertex_size, last_vertex);
  (void)rc;

  free(vertex_data);

  return 0;
}