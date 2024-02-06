#include <stdlib.h>
#include <string.h>

#include "hiredis.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL || ac->err) {
    return 0;
  }

  redisAsyncSetConnectCallback(ac, NULL);
  redisAsyncSetDisconnectCallback(ac, NULL);

  redisAsyncRead(ac);

  redisAsyncFree(ac);
  return 0;
}