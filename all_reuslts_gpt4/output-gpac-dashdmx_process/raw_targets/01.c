#include <fuzzer/FuzzedDataProvider.h>
#include <gpac/filters.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  GF_Filter *filter = nullptr;
  GF_Err e;

  // Initialize filter session
  GF_FilterSession *fsess = gf_fs_new_defaults(0);
  if (fsess == nullptr) {
    return 0;
  }

  // Load a filter
  filter = gf_fs_load_filter(fsess, "dashdmx", &e);
  if (filter == nullptr) {
    gf_fs_del(fsess);
    return 0;
  }

  // Process the filter
  dashdmx_process(filter);

  // Clean up
  gf_fs_del(fsess);

  return 0;
}