 #include <stdlib.h>
#include "hiredis.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    struct redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
    if (ac == NULL) {
        return 0;
    }

    redisProcessCallbacks(ac);
    redisAsyncFree(ac);
    return 0;
}