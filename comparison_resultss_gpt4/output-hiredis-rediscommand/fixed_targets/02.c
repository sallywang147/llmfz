#include <fuzzer/FuzzedDataProvider.h>
#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string format = stream.ConsumeRandomLengthString();

  // Create a redis context
  redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL || c->err) {
    if (c) {
      redisFree(c);
    }
    return 0;
  }

  // Call the target function
  char *reply = redisCommand(c, format.c_str());

  // Free the memory
  if (reply != NULL) {
    freeReplyObject(reply);
  }

  redisFree(c);

  return 0;
}