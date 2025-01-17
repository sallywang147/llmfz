#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include "h2o.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the memory pool
  h2o_mem_pool_t pool;
  h2o_mem_init_pool(&pool);

  // Consume data from the stream
  int quality = stream.ConsumeIntegral<int>();
  size_t bufsz = stream.ConsumeIntegral<size_t>();
  size_t capacity = stream.ConsumeIntegral<size_t>();

  // Call the target function
  struct st_h2o_compress_context_t * ctx = h2o_compress_brotli_open(&pool, quality, bufsz, capacity);

  // Clean up
  h2o_mem_clear_pool(&pool);

  return 0;
}