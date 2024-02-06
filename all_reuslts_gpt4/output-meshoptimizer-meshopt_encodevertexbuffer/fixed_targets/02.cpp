#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "meshoptimizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    const size_t vertex_size = stream.ConsumeIntegralInRange<size_t>(1, 16);
    const size_t vertex_count = stream.ConsumeIntegralInRange<size_t>(1, 1000);
    const size_t buffer_size = vertex_count * vertex_size;

    std::vector<char> buffer(buffer_size);
    std::vector<char> vertices = stream.ConsumeBytes<char>(vertex_count * vertex_size);

    if (vertices.size() < vertex_count * vertex_size) {
        return 0;
    }

    meshopt_encodeVertexBuffer(buffer.data(), buffer_size, vertices.data(), vertex_count, vertex_size);

    return 0;
}