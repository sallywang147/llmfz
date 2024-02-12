#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
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
  redisAsyncCommand(c, NULL, NULL, "SET %b %b", fdp.ConsumeRandomLengthString(10),
                    fdp.ConsumeRandomLengthString(10));
  redisAsyncRead(c);
  redisAsyncFree(c);
  return 0;
}