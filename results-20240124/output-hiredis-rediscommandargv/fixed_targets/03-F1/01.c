#include <stdlib.h>
#include <string.h>
#include "hiredis.h"

extern "C" {
#include "redis.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *new_str, **argv;
    int argc;
    size_t *argvlen;

    if (size < 3)
        return 0;

    new_str = malloc(size+1);
    if (new_str == NULL)
        return 0;

    memcpy(new_str, data, size);
    new_str[size] = '\0';

    if (redisFormatCommandArgv(&argv, &argc, &argvlen, new_str) != -1) {
        redisCommandArgv(NULL, argc, argv, argvlen);
        for (int i = 0; i < argc; i++)
            free(argv[i]);
        free(argv);
    }

    free(new_str);
    return 0;
}