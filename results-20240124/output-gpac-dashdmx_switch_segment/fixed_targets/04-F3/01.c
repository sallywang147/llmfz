#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <gpac/constants.h>
#include <gpac/dashdmx.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct GF_DASHDmxCtx *ctx = gf_dashdmx_new();
  struct GF_DASHGroup *group = gf_dashdmx_new_group(ctx);
  dashdmx_switch_segment(ctx, group);
  gf_dashdmx_delete(ctx);
  return 0;
}