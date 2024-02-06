#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t vertex_count = 66; // must be divisible by 3 for decodeIndexBuffer; should be >=64 to cover large vertex blocks
  size_t vertex_size = 16; // must be divisible by 4

  char *vertex_data = (char *)malloc(vertex_count * vertex_size);
  assert(vertex_data);

  char *last_vertex = vertex_data + (vertex_count - 1) * vertex_size;

  // decodeVertexBlock supports any strides divisible by 4 in 4-256 interval
  // It's a waste of time to check all of them, so we'll just check a few with different alignment mod 16
  meshopt::decodeVertexBlock(reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + size, vertex_data, vertex_count, vertex_size, last_vertex);
  meshopt::decodeVertexBlock(reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + size, vertex_data, vertex_count, vertex_size, last_vertex + 1);
  meshopt::decodeVertexBlock(reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + size, vertex_data, vertex_count, vertex_size, last_vertex + 2);
  meshopt::decodeVertexBlock(reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + size, vertex_data, vertex_count, vertex_size, last_vertex + 3);

  free(vertex_data);

  return 0;
}