#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume values for vertex_count and vertex_size
  size_t vertex_count = stream.ConsumeIntegral<size_t>();
  size_t vertex_size = stream.ConsumeIntegral<size_t>();

  // Consume data for vertex_data and last_vertex
  std::vector<char> vertex_data_vector = stream.ConsumeBytes<char>(vertex_count * vertex_size);
  char* vertex_data = vertex_data_vector.data();

  std::vector<char> last_vertex_vector = stream.ConsumeBytes<char>(vertex_size);
  char* last_vertex = last_vertex_vector.data();

  // Consume data for data and data_end
  size_t data_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::vector<char> data_vector = stream.ConsumeBytes<char>(data_size);
  char* data = data_vector.data();
  char* data_end = data + data_size;

  // Call the function
  meshopt::decodeVertexBlock(data, data_end, vertex_data, vertex_count, vertex_size, last_vertex);

  return 0;
}