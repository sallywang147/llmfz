#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "h2o.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize memory pool
  h2o_mem_pool_t pool;
  h2o_mem_init_pool(&pool);

  // Extract parameters for h2o_compress_brotli_open
  int quality = stream.ConsumeIntegralInRange<int>(0, 11);
  size_t bufsz = stream.ConsumeIntegral<size_t>();
  size_t textsize = stream.ConsumeIntegral<size_t>();

  // Call the function
  struct st_h2o_compress_context_t *context = h2o_compress_brotli_open(&pool, quality, bufsz, textsize);

  // Clean up
  h2o_mem_clear_pool(&pool);

  return 0;
}