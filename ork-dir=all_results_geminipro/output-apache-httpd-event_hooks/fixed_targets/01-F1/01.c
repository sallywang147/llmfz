#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "apr.h"
#include "apr_pools.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  apr_pool_t* pool;
  apr_status_t rv = apr_pool_create(&pool, nullptr);
  if (rv != APR_SUCCESS) {
    return 0;
  }

  event_hooks(pool);

  apr_pool_destroy(pool);
  return 0;
}