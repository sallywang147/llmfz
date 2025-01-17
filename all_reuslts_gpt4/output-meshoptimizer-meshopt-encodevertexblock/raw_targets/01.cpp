#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need two buffers: one for the input vertex data, and one for the output encoded data.
  // We'll split the input data into two halves to fill these buffers.
  size_t half_size = size / 2;
  std::vector<char> vertex_data = stream.ConsumeBytes<char>(half_size);
  std::vector<char> encoded_data(half_size);

  // The vertex size is a parameter to the function, so we need to choose a sensible value.
  // It must be at least 1, and not larger than the size of the vertex data buffer.
  // We'll use a power of two to keep things simple.
  size_t vertex_size = 1;
  while (vertex_size * 2 <= vertex_data.size()) {
    vertex_size *= 2;
  }

  // The vertex count is the number of vertices in the input data.
  // It must be such that vertex_count * vertex_size <= vertex_data.size().
  size_t vertex_count = vertex_data.size() / vertex_size;

  // The last_vertex parameter is a pointer to the "last" vertex in the input data.
  // We'll just point it to the start of the input data for simplicity.
  char* last_vertex = vertex_data.data();

  // Now we can call the function.
  char* result = meshopt::encodeVertexBlock(
      encoded_data.data(), encoded_data.data() + encoded_data.size(),
      vertex_data.data(), vertex_count, vertex_size, last_vertex);

  // We don't actually do anything with the result, since this is a fuzzing harness.
  // The purpose is to check for crashes, not to check the function's output.

  return 0;
}