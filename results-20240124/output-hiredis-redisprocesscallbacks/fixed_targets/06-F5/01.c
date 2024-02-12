#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
}

void redisAsyncConnectCallback(const redisAsyncContext *ac, int status) {
  if (status != REDIS_OK) {
    printf("Error: %s\n", ac->errstr);
    return;
  }

  printf("Connected to Redis\n");
}

void redisProcessCallbacks(struct redisAsyncContext *ac) {
  int status;
  while (1) {
    status = redisAsyncHandleConnect(ac);
    if (status != REDIS_OK) {
      printf("Error: %s\n", ac->errstr);
      return;
    }

    status = redisAsyncHandleRead(ac);
    if (status != REDIS_OK) {
      printf("Error: %s\n", ac->errstr);
      return;
    }

    status = redisAsyncHandleWrite(ac);
    if (status != REDIS_OK) {
      printf("Error: %s\n", ac->errstr);
      return;
    }
  }
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *ac = redisAsyncConnect((const char *)"127.0.0.1", 6379);
  if (ac == NULL) {
    printf("Error: %s\n", ac->errstr);
    return 0;
  }

  redisAsyncSetConnectCallback(ac, redisAsyncConnectCallback);
  redisProcessCallbacks(ac);

  redisAsyncDisconnect(ac);

  return 0;
}