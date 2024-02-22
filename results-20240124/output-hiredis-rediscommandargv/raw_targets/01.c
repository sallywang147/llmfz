 #include <stdlib.h>
#include <string.h>
#include "hiredis.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *new_str, **argv;
    size_t *argvlen;
    int argc;
    struct redisContext *c;

    if (size < 3)
        return 0;

    new_str = malloc(size+1);
    if (new_str == NULL)
        return 0;

    memcpy(new_str, data, size);
    new_str[size] = '\0';

    c = redisConnect("localhost", 6379);
    redisCommandArgv(c, argc, argv, argvlen);
    redisFree(c);

    free(new_str);
    return 0;
}