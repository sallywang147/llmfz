#include "../../src/common/clib-package.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <unistd.h>
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
    char *dir = strdup("/tmp/libfuzzer");
    clib_package_install_executable(pkg, dir, 0);
    free(dir);
    clib_package_free(pkg);
  }
  unlink(filename);
  return 0;
}