#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for the vertex_data
  size_t vertex_data_size = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::vector<char> vertex_data = stream.ConsumeBytes<char>(vertex_data_size);

  // Consume data for the last_vertex
  size_t last_vertex_size = stream.ConsumeIntegralInRange<size_t>(0, size - vertex_data_size);
  std::vector<char> last_vertex = stream.ConsumeBytes<char>(last_vertex_size);

  // The remaining data will be used for the data buffer
  std::vector<char> data_buffer = stream.ConsumeRemainingBytes<char>();
  char* data_end = data_buffer.data() + data_buffer.size();

  // Calculate the vertex_size and vertex_count based on the remaining data
  size_t vertex_size = vertex_data_size > 0 ? stream.ConsumeIntegralInRange<size_t>(1, vertex_data_size) : 1;
  size_t vertex_count = vertex_data_size / vertex_size;

  // Call the function to fuzz
  meshopt::encodeVertexBlock(data_buffer.data(), data_end, vertex_data.data(), vertex_count, vertex_size, last_vertex.data());

  return 0;
}