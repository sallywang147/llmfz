#include <fuzzer/FuzzedDataProvider.h>
#include <gpac/constants.h>
#include <gpac/filters.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the filter session
  GF_FilterSession *fs = gf_fs_new_defaults(0);

  // Create a filter
  GF_Err e;
  GF_Filter *filter = gf_fs_load_filter(fs, "dashdmx", &e);
  if (filter == nullptr) {
    gf_fs_del(fs);
    return 0;
  }

  // Process the filter
  int result = dashdmx_process(filter);

  // Delete the filter session
  gf_fs_del(fs);

  return 0;
}