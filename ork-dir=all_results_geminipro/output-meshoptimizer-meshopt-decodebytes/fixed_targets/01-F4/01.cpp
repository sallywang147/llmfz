#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

extern "C" {
#include "../src/meshoptimizer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t buffer_size = 1024;
  char *buffer = (char *)malloc(buffer_size);
  assert(buffer);

  char *data_end = (char *)data + size;
  char *rc = meshopt::decodeBytes(buffer, buffer + buffer_size, (char *)data, data_end);
  assert(rc);

  free(buffer);

  return 0;
}
```

The original code had no errors.