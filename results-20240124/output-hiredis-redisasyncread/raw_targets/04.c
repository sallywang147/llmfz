 #include <stdlib.h>
#include <string.h>
#include "hiredis.h"
#include "async.h"

struct redisAsyncContext *ac;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *new_str, *cmd;

    if (size < 3)
        return 0;

    new_str = malloc(size+1);
    if (new_str == NULL)
        return 0;

    memcpy(new_str, data, size);
    new_str[size] = '\0';

    if (redisFormatCommand(&cmd, new_str) != -1) {
        hi_free(cmd);
    }

    redisAsyncRead(ac);

    free(new_str);
    return 0;
}