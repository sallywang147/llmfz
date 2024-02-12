 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "h2o.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t quality = stream.ConsumeIntegralInRange<size_t>(0, 11);
  size_t window_size = stream.ConsumeIntegralInRange<size_t>(10, 24);
  struct st_h2o_mem_pool_t *pool = h2o_mem_pool_create();
  struct st_h2o_compress_context_t *ctx =
      h2o_compress_brotli_open(pool, quality, window_size, 0);
  if (ctx == nullptr) {
    return 0;
  }
  h2o_compress_brotli_close(ctx);
  h2o_mem_pool_release(pool);
  return 0;
}