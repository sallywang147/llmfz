#include <fuzzer/FuzzedDataProvider.h>
#include "H5Dpkg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a H5D_t object
  H5D_t dataset;
  dataset.shared = (H5D_shared_t*)calloc(1, sizeof(H5D_shared_t));
  dataset.oloc.file = (H5F_t*)calloc(1, sizeof(H5F_t));
  dataset.oloc.file->shared = (H5F_shared_t*)calloc(1, sizeof(H5F_shared_t));

  // Call the target function
  H5D__get_space(&dataset);

  // Clean up
  free(dataset.oloc.file->shared);
  free(dataset.oloc.file);
  free(dataset.shared);

  return 0;
}