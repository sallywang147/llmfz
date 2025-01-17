#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t vertex_size = stream.ConsumeIntegralInRange<size_t>(1, 16);
  size_t vertex_count = stream.ConsumeIntegralInRange<size_t>(1, 100);
  size_t total_vertex_data_size = vertex_count * vertex_size;

  std::vector<char> vertex_data(total_vertex_data_size, 0);
  std::vector<char> last_vertex(vertex_size, 0);

  size_t remaining_size = stream.remaining_bytes();
  std::vector<char> input_data = stream.ConsumeBytes<char>(remaining_size);

  char* data_end = input_data.data() + remaining_size;

  meshopt::decodeVertexBlock(input_data.data(), data_end, vertex_data.data(), vertex_count, vertex_size, last_vertex.data());

  return 0;
}