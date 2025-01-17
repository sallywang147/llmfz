#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "jbig2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the JBIG2 context
  Jbig2Ctx *ctx = jbig2_ctx_new(nullptr, JBIG2_OPTIONS_EMBEDDED, nullptr, nullptr, nullptr);
  if (ctx == nullptr) {
    return 0;
  }

  // Create a global context
  Jbig2GlobalCtx* global_ctx = jbig2_make_global_ctx(ctx);
  if (global_ctx == nullptr) {
    jbig2_ctx_free(ctx);
    return 0;
  }

  // Call the function to fuzz
  struct _Jbig2Allocator *allocator = jbig2_global_ctx_free(global_ctx);

  // Cleanup
  jbig2_ctx_free(ctx);

  return 0;
}