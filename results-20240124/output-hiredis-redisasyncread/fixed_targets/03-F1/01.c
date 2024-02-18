#include <hiredis.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL)
    return 0;

  redisAsyncSetConnectCallback(ac, NULL);
  redisAsyncSetDisconnectCallback(ac, NULL);

  redisAsyncCommand(ac, NULL, NULL, "PING");
  redisAsyncHandleReply(ac, NULL);

  redisAsyncDisconnect(ac);
  return 0;
}