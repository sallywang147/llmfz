#include <apr_pools.h>

extern "C" {
#include "llvm/FuzzMutate.h"
}

void event_hooks(apr_pool_t *pool) {
  // Your code here
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  apr_pool_t *pool = apr_pool_create_default(NULL);
  event_hooks(pool);
  apr_pool_destroy(pool);
  return 0;
}