#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "jbig2.h"

extern "C" {
#include "jbig2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct _Jbig2GlobalCtx* global_ctx = jbig2_global_ctx_new();
  if (global_ctx == nullptr) {
    return 0;
  }
  jbig2_global_ctx_free(global_ctx);
  return 0;
}