#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gpac/dashdmx.h"

extern "C" {
#include "gpac/gf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gf_init();
    initialized = true;
  }

  GF_DASHDmxCtx *ctx = gf_dashdmx_new();
  if (ctx == nullptr) {
    return 0;
  }

  GF_DASHGroup *group = gf_dashdmx_new_group(ctx, NULL, NULL, NULL);
  if (group == nullptr) {
    gf_dashdmx_delete(ctx);
    return 0;
  }

  dashdmx_switch_segment(ctx, group);

  gf_dashdmx_delete_group(group);
  gf_dashdmx_delete(ctx);

  return 0;
}