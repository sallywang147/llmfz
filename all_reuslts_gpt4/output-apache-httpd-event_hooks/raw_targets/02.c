#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "apr_pools.h"

extern void event_hooks(struct apr_pool_t * p);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  apr_status_t rv;
  apr_pool_t *p = NULL;

  rv = apr_initialize();
  if (rv != APR_SUCCESS) {
    return 0;
  }

  rv = apr_pool_create(&p, NULL);
  if (rv != APR_SUCCESS) {
    apr_terminate();
    return 0;
  }

  event_hooks(p);

  apr_pool_destroy(p);
  apr_terminate();

  return 0;
}