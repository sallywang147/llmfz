#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "apr_pools.h"

extern "C" {
    void event_hooks(struct apr_pool_t * p);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    static bool initialized = false;
    if (!initialized) {
        apr_initialize();
        atexit(apr_terminate);
        initialized = true;
    }

    apr_pool_t *pool;
    apr_pool_create(&pool, NULL);

    event_hooks(pool);

    apr_pool_destroy(pool);
    return 0;
}