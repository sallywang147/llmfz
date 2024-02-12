#include <gpac/filters.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <algorithm>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct __gf_filter *filter = gf_filter_create();
  gf_filter_set_input(filter, data, size);
  dashdmx_process(filter);
  gf_filter_delete(filter);
  return 0;
}
}