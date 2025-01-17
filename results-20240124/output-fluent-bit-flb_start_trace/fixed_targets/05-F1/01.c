#include <fluent-bit/flb_lib.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <fluent-bit/flb_info.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct flb_lib_ctx *ctx = flb_lib_ctx_create();
  if (ctx == NULL) {
    return 0;
  }

  flb_start_trace(ctx);
  flb_lib_ctx_destroy(ctx);

  return 0;
}