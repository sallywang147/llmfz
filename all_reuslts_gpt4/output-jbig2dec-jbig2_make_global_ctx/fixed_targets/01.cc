#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the JBIG2 decoder context
  Jbig2Ctx *ctx = jbig2_ctx_new(NULL, JBIG2_OPTIONS_EMBEDDED, NULL, NULL, NULL);
  if (ctx == nullptr) {
    return 0;
  }

  // Create a JBIG2 global context
  Jbig2GlobalCtx *global_ctx = jbig2_make_global_ctx(ctx);
  if (global_ctx == nullptr) {
    jbig2_ctx_free(ctx);
    return 0;
  }

  // Clean up
  jbig2_global_ctx_free(global_ctx);
  jbig2_ctx_free(ctx);

  return 0;
}