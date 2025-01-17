#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "htmlparser.h"

extern "C" {
#include "scanentities.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *copy = (char *)malloc(size + 1);
  memcpy(copy, data, size);
  copy[size] = '\0';

  _scan_entity(copy);

  free(copy);
  return 0;
}
```

The `scanentities.h` header file should include the definition of the `_scan_entity` function.

The `extern "C" {}` block is used to wrap the `#include` directive for the `scanentities.h` header file. This is necessary because the `_scan_entity` function is declared in a C header file, and the C++ compiler needs to be told to look for it in the C standard library.