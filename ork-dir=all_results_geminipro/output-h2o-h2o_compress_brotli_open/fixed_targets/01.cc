#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_mem_pool_t* pool = h2o_mem_pool_create();
  if (pool == nullptr) {
    return 0;
  }
  int quality = stream.ConsumeIntegral<int>();
  size_t window = stream.ConsumeIntegral<size_t>();
  size_t block = stream.ConsumeIntegral<size_t>();
  struct st_h2o_compress_context_t* ctx =
      h2o_compress_brotli_open(pool, quality, window, block);
  if (ctx == nullptr) {
    h2o_mem_pool_release(pool);
    return 0;
  }
  h2o_compress_brotli_close(ctx);
  h2o_mem_pool_release(pool);
  return 0;
}