 #include <hiredis.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    struct redisAsyncContext *ac = redisAsyncConnect("localhost", 6379);
    redisProcessCallbacks(ac);
    redisAsyncFree(ac);
    return 0;
}