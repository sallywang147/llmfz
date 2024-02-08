#include "../../src/common/clib-package.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
#include <clib-package.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }
  char filename[256];
  sprintf(filename, "libfuzzer.json");

  FILE *fp = fopen(filename, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  clib_package_t *pkg = clib_package_load_from_manifest(filename, 0);
  if (pkg) {
    char dir[256];
    sprintf(dir, "libfuzzer");
    clib_package_install(pkg, dir, 0);
    clib_package_free(pkg);
  }
  unlink(filename);
  return 0;
}
```

The issue was that the header `clib-package.h` was included twice, once with `extern "C" {}` and once without. This caused a compiler error because the header was defined twice. To fix this, the header `clib-package.h` was included only once, with `extern "C" {}`.