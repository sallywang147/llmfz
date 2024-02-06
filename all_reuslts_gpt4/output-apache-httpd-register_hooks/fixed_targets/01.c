#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "apr_pools.h"

extern void register_hooks(struct apr_pool_t * p);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    apr_initialize();
    atexit(apr_terminate);
    initialized = true;
  }

  apr_pool_t *pool;
  if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
    return 0;
  }

  register_hooks(pool);

  apr_pool_destroy(pool);

  return 0;
}