#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the jbig2 context
  Jbig2Ctx *ctx = jbig2_ctx_new(NULL, (Jbig2Options)0, NULL, NULL, NULL);
  if (ctx == NULL) {
    return 0;
  }

  // Create a global context
  Jbig2GlobalCtx *global_ctx = jbig2_make_global_ctx(ctx);

  // Cleanup
  jbig2_global_ctx_free(global_ctx);
  jbig2_ctx_free(ctx);

  return 0;
}