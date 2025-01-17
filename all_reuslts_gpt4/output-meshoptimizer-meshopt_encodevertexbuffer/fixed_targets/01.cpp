#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We'll divide the available data into two parts: one for the buffer and one for the vertices.
  size_t buffer_size = stream.remaining_bytes() / 2;
  size_t vertex_size = sizeof(char); // each vertex is a char

  // Ensure we have at least one vertex to avoid division by zero
  if (buffer_size < vertex_size) {
    return 0;
  }

  // The number of vertices is determined by the size of the remaining data divided by the size of each vertex.
  size_t vertex_count = buffer_size / vertex_size;

  // Consume the data for the buffer and vertices
  std::vector<char> buffer = stream.ConsumeBytes<char>(buffer_size);
  std::vector<char> vertices = stream.ConsumeBytes<char>(vertex_count * vertex_size);

  // Call the function under test
  meshopt_encodeVertexBuffer(buffer.data(), buffer_size, vertices.data(), vertex_count, vertex_size);

  return 0;
}