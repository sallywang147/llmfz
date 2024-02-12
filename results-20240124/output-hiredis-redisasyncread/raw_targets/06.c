 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  redisAsyncContext* context = redisAsyncConnect("localhost", 6379);
  if (context == nullptr) {
    return 0;
  }

  redisAsyncSetConnectCallback(context, [](const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
      return;
    }
    redisAsyncRead(c);
  });

  redisAsyncSetDisconnectCallback(context, [](const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
      return;
    }
    redisAsyncFree(c);
  });

  redisAsyncSetReadCallback(context, [](redisAsyncContext *c, void *r, void *privdata) {
    redisReply* reply = reinterpret_cast<redisReply*>(r);
    if (reply->type == REDIS_REPLY_ERROR) {
      return;
    }
    redisAsyncRead(c);
  });

  redisAsyncSetWriteCallback(context, [](redisAsyncContext *c, void *r, void *privdata) {
    redisAsyncRead(c);
  });

  redisAsyncHandleConnect(context);
  redisAsyncHandleWrite(context);
  redisAsyncHandleRead(context);
  redisAsyncHandleDisconnect(context);

  return 0;
}