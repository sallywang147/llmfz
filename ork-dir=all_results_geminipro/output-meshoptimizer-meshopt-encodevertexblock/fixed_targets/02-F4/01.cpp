#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <assert.h>
#include <stdio.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // We'll pick a random vertex count between 1 and 1000
  size_t vertex_count = 1 + rand() % 1000;

  // We'll pick a random vertex size between 1 and 256
  size_t vertex_size = 1 + rand() % 256;

  // We'll allocate memory for the vertex data
  char *vertex_data = (char*)malloc(vertex_count * vertex_size);
  assert(vertex_data);

  // We'll fill the vertex data with random values
  for (size_t i = 0; i < vertex_count * vertex_size; ++i) {
    vertex_data[i] = rand();
  }

  // We'll allocate memory for the encoded data
  size_t encoded_size = vertex_count * vertex_size * 2;
  char *encoded_data = (char*)malloc(encoded_size);
  assert(encoded_data);

  // We'll call the encodeVertexBlock function
  char *encoded_end = meshopt::encodeVertexBlock(encoded_data, encoded_data + encoded_size, vertex_data, vertex_count, vertex_size, vertex_data);

  // We'll free the allocated memory
  free(vertex_data);
  free(encoded_data);

  return 0;
}