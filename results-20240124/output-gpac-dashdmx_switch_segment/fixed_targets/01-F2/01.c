#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "dashdmx.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    dashdmx_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  struct GF_DASHDmxCtx *ctx = dashdmx_new();
  if (ctx == nullptr) {
    return 0;
  }

  struct GF_DASHGroup *group = dashdmx_new_group(ctx);
  if (group == nullptr) {
    dashdmx_free(ctx);
    return 0;
  }

  dashdmx_switch_segment(ctx, group);

  dashdmx_free_group(group);
  dashdmx_free(ctx);

  return 0;
}