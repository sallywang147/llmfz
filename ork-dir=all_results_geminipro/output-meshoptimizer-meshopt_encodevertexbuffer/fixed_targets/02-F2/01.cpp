#include "../src/meshoptimizer.h"

#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <meshoptimizer.h>
}

void fuzzEncoder(const uint8_t *data, size_t size, size_t stride, int (*encode)(void *, size_t, const void *, size_t, size_t)) {
  size_t count = 66; // must be divisible by 3 for decodeIndexBuffer; should be >=64 to cover large vertex blocks

  void *vertices = malloc(count * stride);
  assert(vertices);

  size_t buffer_size = meshopt_encodeVertexBufferBound(count, stride);
  void *buffer = malloc(buffer_size);
  assert(buffer);

  size_t encoded_size = encode(buffer, buffer_size, vertices, count, stride);
  (void)encoded_size;

  free(buffer);
  free(vertices);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // encodeVertexBuffer supports any strides divisible by 4 in 4-256 interval
  // It's a waste of time to check all of them, so we'll just check a few with different alignment mod 16
  fuzzEncoder(data, size, 4, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 16, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 24, meshopt_encodeVertexBuffer);
  fuzzEncoder(data, size, 32, meshopt_encodeVertexBuffer);

  return 0;
}
```

The issue is that the header file `meshoptimizer.h` is included twice: once in the `#include "../src/meshoptimizer.h"` line and again in the `#include <meshoptimizer.h>` line. This causes a compiler error because the header file defines multiple times the same symbols, which is not allowed.

To fix this issue, remove one of the `#include` lines. In this case, we can remove the `#include <meshoptimizer.h>` line because we already include the header file in the `#include "../src/meshoptimizer.h"` line.

After removing the `#include <meshoptimizer.h>` line, the code should compile without errors.