#include "hiredis.h"
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL || ac->err) {
    return 0;
  }
  redisProcessCallbacks(ac);
  redisAsyncFree(ac);
  return 0;
}