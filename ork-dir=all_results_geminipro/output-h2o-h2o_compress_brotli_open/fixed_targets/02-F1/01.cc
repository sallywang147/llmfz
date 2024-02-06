#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "h2o.h"

extern "C" {
#include "h2o/compress.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_mem_pool_t* pool = h2o_mem_pool_create();
  const int quality = stream.ConsumeIntegral<int>();
  const size_t window_size = stream.ConsumeIntegral<size_t>();
  const size_t block_size = stream.ConsumeIntegral<size_t>();
  struct st_h2o_compress_context_t* ctx = h2o_compress_brotli_open(
      pool, quality, window_size, block_size);
  if (ctx == nullptr) {
    return 0;
  }
  h2o_compress_brotli_close(ctx);
  h2o_mem_pool_release(pool);
  return 0;
}