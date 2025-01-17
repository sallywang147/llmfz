#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <redis/async.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <redis/async.h>
}

void redisProcessCallbacks(struct redisAsyncContext *ac) {
  while (1) {
    void *reply = redisAsyncGetReply(ac);
    if (reply == NULL) break;
    redisReply *r = (redisReply *)reply;
    printf("%s\n", r->str);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL) {
    return 0;
  }
  redisAsyncSetConnectCallback(ac, redisProcessCallbacks);
  redisAsyncCommand(ac, NULL, NULL, "SET %s %s", fdp.ConsumeRandomLengthString(10).c_str(), fdp.ConsumeRandomLengthString(10).c_str());
  redisAsyncHandleConnect(ac);
  redisAsyncFree(ac);
  return 0;
}