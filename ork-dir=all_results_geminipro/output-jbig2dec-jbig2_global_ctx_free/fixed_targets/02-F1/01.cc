#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "jbig2.h"

extern "C" {
#include "jbig2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t global_ctx_size = stream.ConsumeIntegral<uint8_t>();
  Jbig2GlobalCtx* global_ctx =
      static_cast<Jbig2GlobalCtx*>(std::malloc(global_ctx_size));
  if (global_ctx == nullptr) {
    return 0;
  }
  std::memset(global_ctx, 0, global_ctx_size);

  jbig2_global_ctx_free(global_ctx);
  return 0;
}