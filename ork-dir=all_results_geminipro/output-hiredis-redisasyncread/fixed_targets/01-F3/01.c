#include <stdlib.h>
#include <string.h>

#include "hiredis.h"
#include "hiredis/sds.h"

extern "C" {
#include <hiredis/async.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL || ac->err) {
    return 0;
  }

  redisAsyncSetConnectCallback(ac, NULL);
  redisAsyncSetDisconnectCallback(ac, NULL);

  redisAsyncCommand(ac, NULL, NULL, "SET key %b", size, data);
  redisAsyncRead(ac);

  redisAsyncFree(ac);
  return 0;
}