#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

static redisAsyncContext *ac;

static void connectCallback(const redisAsyncContext *ac, int status) {
  if (status != REDIS_OK) {
    fprintf(stderr, "Error: %s\n", ac->errstr);
    return;
  }
  printf("Connected to Redis\n");
}

static void disconnectCallback(const redisAsyncContext *ac, int status) {
  if (status != REDIS_OK) {
    fprintf(stderr, "Error: %s\n", ac->errstr);
    return;
  }
  printf("Disconnected from Redis\n");
  redisAsyncFree(ac);
}

static void redisProcessCallbacks(struct redisAsyncContext *ac) {
  int status;
  do {
    status = redisAsyncHandleRead(ac);
  } while (status > 0);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (ac == NULL) {
    ac = redisAsyncConnect("127.0.0.1", 6379);
    if (ac == NULL) {
      fprintf(stderr, "Error: %s\n", ac->errstr);
      return 0;
    }
    redisAsyncSetConnectCallback(ac, connectCallback);
    redisAsyncSetDisconnectCallback(ac, disconnectCallback);
  }
  redisProcessCallbacks(ac);
  return 0;
}