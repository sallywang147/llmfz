#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // We'll decode the data first, then re-encode it and compare the results
  size_t count = 66; // must be divisible by 3 for decodeIndexBuffer; should be >=64 to cover large vertex blocks

  void *destination = malloc(count * 4);
  assert(destination);

  int rc = meshopt_decodeIndexBuffer(destination, count, 4, reinterpret_cast<const unsigned char *>(data), size);
  assert(rc == 0);

  // encodeVertexBlock supports any strides divisible by 4 in 4-256 interval
  // It's a waste of time to check all of them, so we'll just check a few with different alignment mod 16
  size_t strides[] = {4, 16, 24, 32};
  for (size_t i = 0; i < sizeof(strides) / sizeof(strides[0]); ++i) {
    size_t stride = strides[i];

    char *output = new char[count * stride];
    assert(output);

    char *last_vertex = nullptr;
    char *vertex_data = reinterpret_cast<char *>(destination);

    char *data_end = output + count * stride;

    char *end = meshopt::encodeVertexBlock(output, data_end, vertex_data, count, stride, last_vertex);

    assert(end <= data_end);

    // Check that we can decode the encoded data back to the original vertex data
    rc = meshopt_decodeIndexBuffer(destination, count, 4, reinterpret_cast<const unsigned char *>(output), end - output);
    assert(rc == 0);

    rc = memcmp(destination, vertex_data, count * stride);
    assert(rc == 0);

    delete[] output;
  }

  free(destination);

  return 0;
}