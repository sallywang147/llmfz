#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "flb_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    flb_lib_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  
  struct flb_lib_ctx *ctx = flb_lib_init("tcp://127.0.0.1:24224");
  if (ctx == NULL) {
    return 0;
  }

  flb_start_trace(ctx);

  flb_lib_exit(ctx);

  return 0;
}