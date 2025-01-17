#include "../../src/common/clib-package.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  char filename[256];
  sprintf(filename, "libfuzzer.json");

  FILE *fp = fopen(filename, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  clib_package_t *pkg = clib_package_load_from_manifest(filename, 0);
  if (pkg) {
    int verbose = stream.ConsumeIntegralInRange<int>(0, 1);
    char dir[256];
    sprintf(dir, "libfuzzer_dir");
    mkdir(dir, 0700);
    clib_package_install_development(pkg, dir, verbose);
    clib_package_free(pkg);
    rmdir(dir);
  }
  unlink(filename);
  return 0;
}