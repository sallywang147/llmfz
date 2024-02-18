#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c == NULL) {
        return 0;
    }
    redisAsyncSetConnectCallback(c, NULL);
    redisAsyncSetDisconnectCallback(c, NULL);
    redisAsyncSetWriteCallback(c, NULL);
    redisAsyncSetReadCallback(c, NULL);
    redisProcessCallbacks(c);
    redisAsyncFree(c);
    return 0;
}