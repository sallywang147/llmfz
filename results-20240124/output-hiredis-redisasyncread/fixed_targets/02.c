#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
#include <hiredis/sds.h>
}

static void getCallback(redisAsyncContext *c, void *r, void *privdata) {
  (void)c;
  (void)r;
  (void)privdata;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
  if (c->err) {
    return 0;
  }
  redisAsyncSetConnectCallback(c, getCallback);
  sds key = sdsnew(fdp.ConsumeRandomLengthString(10).c_str());
  sds value = sdsnew(fdp.ConsumeRandomLengthString(10).c_str());
  redisAsyncCommand(c, NULL, NULL, "SET %s %s", key, value);
  redisAsyncHandleConnect(c);
  redisAsyncFree(c);
  sdsfree(key);
  sdsfree(value);
  return 0;
}