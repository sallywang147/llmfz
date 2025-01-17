#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "h2o.h"
#include "h2o/compress.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t quality = provider.ConsumeIntegralInRange<size_t>(0, 11);
  size_t window_size = provider.ConsumeIntegralInRange<size_t>(0, 24);
  struct st_h2o_compress_context_t* ctx =
      h2o_compress_brotli_open(NULL, quality, window_size, 0);
  if (ctx == nullptr) {
    return 0;
  }
  h2o_compress_brotli_close(ctx);
  return 0;
}