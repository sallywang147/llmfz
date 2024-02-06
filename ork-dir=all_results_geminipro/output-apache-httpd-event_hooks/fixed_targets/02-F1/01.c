#include <fuzzer/FuzzedDataProvider.h>

#include <apr_pools.h>

extern "C" {
#include <apr-1/apr_pools.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  apr_pool_t* pool = nullptr;
  apr_pool_create(&pool, nullptr);
  event_hooks(pool);
  apr_pool_destroy(pool);
  return 0;
}