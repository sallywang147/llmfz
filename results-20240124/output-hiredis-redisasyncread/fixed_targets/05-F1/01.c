#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "hiredis.h"

#ifdef __cplusplus
}
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    struct redisAsyncContext *ac;
    if (size < 3)
        return 0;
    ac = redisAsyncConnect("127.0.0.1", 6379);
    if (ac == NULL)
        return 0;

    redisAsyncRead(ac);
    redisAsyncFree(ac);
    return 0;
}