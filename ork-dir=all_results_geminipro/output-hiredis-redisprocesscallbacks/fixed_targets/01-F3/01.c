#include "hiredis.h"
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "redisAsync.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
  if (c->err) {
    return 0;
  }
  redisAsyncSetConnectCallback(c, connectCallback);
  redisAsyncSetDisconnectCallback(c, disconnectCallback);
  redisAsyncCommand(c, NULL, NULL, "SET key %b", (size_t)size, data);
  redisAsyncHandleConnect(c);
  redisAsyncHandleDisconnect(c);
  redisAsyncFree(c);
  return 0;
}

static void connectCallback(const redisAsyncContext *c, int status) {
  if (status != REDIS_OK) {
    printf("Error: %s\n", c->errstr);
    return;
  }
  printf("Connected to Redis\n");
}

static void disconnectCallback(const redisAsyncContext *c, int status) {
  if (status != REDIS_OK) {
    printf("Error: %s\n", c->errstr);
    return;
  }
  printf("Disconnected from Redis\n");
}