#include <stdlib.h>
#include <string.h>
#include "hiredis.h"

extern "C" {
#include <hiredis/hiredis.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    redisContext *c;
    redisReply *reply;
    char **new_argv;
    size_t *new_argvlen;
    char *ret;
    int i;

    if (size < 3)
        return 0;

    new_argvlen = malloc(sizeof(size_t)*size);
    if (new_argvlen == NULL)
        return 0;

    new_argv = malloc(sizeof(char*)*size);
    if (new_argv == NULL) {
        free(new_argvlen);
        return 0;
    }

    for (i = 0; i < size; i++) {
        new_argvlen[i] = data[i];
        new_argv[i] = malloc(new_argvlen[i]+1);
        if (new_argv[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(new_argv[j]);
            free(new_argv);
            free(new_argvlen);
            return 0;
        }
        memcpy(new_argv[i], data+i+1, new_argvlen[i]);
        new_argv[i][new_argvlen[i]] = '\0';
    }

    c = redisConnect("localhost", 6379);
    if (c == NULL || c->err) {
        if (c) {
            redisFree(c);
        }
        return 0;
    }

    reply = redisCommandArgv(c, size, new_argv, new_argvlen);
    if (reply == NULL) {
        redisFree(c);
        return 0;
    }

    freeReplyObject(reply);
    redisFree(c);

    for (i = 0; i < size; i++)
        free(new_argv[i]);
    free(new_argv);
    free(new_argvlen);
    return 0;
}