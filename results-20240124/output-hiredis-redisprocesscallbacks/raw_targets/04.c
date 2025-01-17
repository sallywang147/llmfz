 #include <hiredis.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  redisProcessCallbacks(ac);
  redisAsyncFree(ac);
  return 0;
}