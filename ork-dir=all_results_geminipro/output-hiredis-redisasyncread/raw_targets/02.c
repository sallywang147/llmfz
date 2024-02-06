#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL || ac->err) {
    return 0;
  }
  redisAsyncRead(ac);
  redisAsyncFree(ac);
  return 0;
}