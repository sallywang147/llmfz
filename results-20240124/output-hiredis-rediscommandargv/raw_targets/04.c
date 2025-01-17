 #include <stdlib.h>
#include <string.h>
#include "hiredis.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char **argv;
    size_t *argvlen;
    char *new_str, *cmd;
    int argc;

    if (size < 3)
        return 0;

    new_str = malloc(size+1);
    if (new_str == NULL)
        return 0;

    memcpy(new_str, data, size);
    new_str[size] = '\0';

    argc = sscanf(new_str, "%d", &argc);
    if (argc < 0)
        return 0;

    argv = malloc(argc * sizeof(char *));
    if (argv == NULL)
        return 0;

    argvlen = malloc(argc * sizeof(size_t));
    if (argvlen == NULL)
        return 0;

    char *ptr = new_str;
    for (int i = 0; i < argc; i++) {
        argv[i] = ptr;
        while (*ptr != ' ')
            ptr++;
        *ptr++ = '\0';
        argvlen[i] = strlen(argv[i]);
    }

    if (redisCommandArgv(NULL, argc, argv, argvlen) != -1)
        hi_free(cmd);

    free(new_str);
    free(argv);
    free(argvlen);
    return 0;
}