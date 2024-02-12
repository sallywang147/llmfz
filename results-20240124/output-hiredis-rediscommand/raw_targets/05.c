 #include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *format = stream.ConsumeRemainingBytesAsString().c_str();
  struct redisContext *c = redisConnect("localhost", 6379);
  if (c != NULL) {
    char *reply = redisCommand(c, format);
    freeReplyObject(reply);
    redisFree(c);
  }
  return 0;
}