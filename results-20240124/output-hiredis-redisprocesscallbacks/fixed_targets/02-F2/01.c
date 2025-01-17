#include <stdlib.h>
#include "hiredis.h"

extern "C" {
#include "async.h"
#include "rio.h"
#include "sds.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
    if (ac == NULL) {
        return 0;
    }

    redisAsyncCommand(ac, NULL, NULL, "SET key %b", size, data);
    redisProcessCallbacks(ac);
    redisAsyncFree(ac);
    return 0;
}