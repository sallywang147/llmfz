#include <stdlib.h>
#include <string.h>
#include "hiredis.h"

extern "C" {
#include "redis.h"
}

void hi_free(void *ptr) {
    free(ptr);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *new_str, *cmd;
    size_t argvlen;
    int argc = 0;
    char **argv;

    if (size < 3)
        return 0;

    new_str = malloc(size+1);
    if (new_str == NULL)
        return 0;

    memcpy(new_str, data, size);
    new_str[size] = '\0';

    argv = malloc(sizeof(char *) * (argc + 1));
    if (argv == NULL)
        return 0;

    argv[argc++] = new_str;
    argv[argc] = NULL;

    if (redisCommandArgv(NULL, argc, argv, &argvlen) == REDIS_OK)
        hi_free(cmd);

    free(new_str);
    free(argv);
    return 0;
}