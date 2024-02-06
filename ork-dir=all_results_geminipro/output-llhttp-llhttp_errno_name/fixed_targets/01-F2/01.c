#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <llhttp.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }

  int err_code = *(int *)data;
  const char *err_name = llhttp_errno_name(err_code);
  if (err_name == NULL) {
    return 0;
  }
  return 0;
}
```

In this code, the issue was that `llhttp_errno_name` returns a `const char*` instead of a `char*`. To fix this, the variable `err_name` is declared as `const char*` instead of `char*`.