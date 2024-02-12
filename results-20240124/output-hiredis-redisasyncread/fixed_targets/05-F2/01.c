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
    redisContext *c;
    if (size < 3)
        return 0;
    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL)
        return 0;

    redisFree(c);
    return 0;
}