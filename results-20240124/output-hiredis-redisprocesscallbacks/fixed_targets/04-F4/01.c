#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <redis.h>
#include <stdint.h>

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

void redisProcessCallbacks(struct redisAsyncContext *ac) {
  int status;
  do {
    status = redisAsyncHandleRead(ac);
  } while (status > 0);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  assert(ac != NULL);
  redisAsyncSetConnectCallback(ac, redisProcessCallbacks);
  redisAsyncConnect(ac);
  redisProcessCallbacks(ac);
  redisAsyncDisconnect(ac);
  redisAsyncFree(ac);
  return 0;
}