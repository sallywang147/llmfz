#include "hiredis.h"
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
  if (c->err) {
    return 0;
  }
  redisProcessCallbacks(c);
  redisAsyncDisconnect(c);
  return 0;
}