#include <stdlib.h>
#include <string.h>
#include "hiredis.h"

extern "C" {
#include <stdio.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *new_str;
    int argc = 2;
    char *argv[] = {"redis-cli", NULL};
    size_t argvlen[] = {strlen(argv[0]), 0};
    struct redisContext *c;

    if (size < 3)
        return 0;

    new_str = malloc(size+1);
    if (new_str == NULL)
        return 0;

    memcpy(new_str, data, size);
    new_str[size] = '\0';

    c = redisConnect("localhost", 6379);
    if (c == NULL) {
        free(new_str);
        return 0;
    }

    redisCommandArgv(c, argc, argv, argvlen);
    redisFree(c);

    free(new_str);
    return 0;
}