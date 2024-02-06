#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a global context
  Jbig2Ctx *ctx = jbig2_ctx_new(NULL, 0, NULL, NULL, NULL);

  // Initialize a global context
  Jbig2GlobalCtx *global_ctx = jbig2_make_global_ctx(ctx);

  // Call the function to fuzz
  jbig2_global_ctx_free(global_ctx);

  // Free the context
  jbig2_ctx_free(ctx);

  return 0;
}