#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "flb.h"

extern "C" {
#include "flb-lib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct flb_lib_ctx* ctx = flb_lib_ctx_new();
  if (ctx == nullptr) {
    return 0;
  }

  int ret = flb_start_trace(ctx);
  flb_lib_ctx_destroy(ctx);
  return ret;
}