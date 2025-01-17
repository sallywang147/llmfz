#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "http_errno.h"
}

extern "C" void free(void *);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }
  int value = *(int *)data;
  const char *result = http_errno_name(value);
  if (result) {
    free((void *)result);
  }
  return 0;
}
```

Changes made:

1. Wrapped the `#include` directive for `http_errno.h` with `extern "C" {}`.
2. Declared the `free` function in the global scope using the `extern` keyword.