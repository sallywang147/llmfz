#include <fuzzer/FuzzedDataProvider.h>
#include <fluent-bit/flb_config.h>
#include <fluent-bit/flb_lib_ctx.h>
#include <fluent-bit/flb_parser.h>
#include <fluent-bit/flb_trace.h>

extern "C" {
#include <algorithm>
#include <fluent-bit/flb_lib_ctx.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct flb_lib_ctx *ctx = flb_lib_ctx_create();
  flb_start_trace(ctx);
  flb_lib_ctx_destroy(ctx);
  return 0;
}