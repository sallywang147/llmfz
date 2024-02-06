#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/common/clib-package.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a temporary directory for installation
  char dir_template[] = "/tmp/clib_package_XXXXXX";
  char* dir = mkdtemp(dir_template);
  if (!dir) {
    return 0;
  }

  // Write the package manifest to a file
  char manifest_path[256];
  snprintf(manifest_path, sizeof(manifest_path), "%s/manifest.json", dir);
  FILE *fp = fopen(manifest_path, "wb");
  if (!fp) {
    return 0;
  }

  auto manifest_data = stream.ConsumeRemainingBytes();
  fwrite(manifest_data.data(), 1, manifest_data.size(), fp);
  fclose(fp);

  // Load the package from the manifest
  clib_package_t *pkg = clib_package_load_from_manifest(manifest_path, 0);
  if (pkg) {
    // Install the package executable
    int verbose = stream.ConsumeBool();
    clib_package_install_executable(pkg, dir, verbose);
    clib_package_free(pkg);
  }

  // Clean up
  remove(manifest_path);
  rmdir(dir);

  return 0;
}