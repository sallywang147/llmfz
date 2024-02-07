#include <fuzzer/FuzzedDataProvider.h>
#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);
  std::string format = stream.ConsumeRemainingBytesAsString();

  // Initialize a redis context
  redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL || c->err) {
    if (c) {
      printf("Error: %s\n", c->errstr);
      // handle error
    } else {
      printf("Can't allocate redis context\n");
    }
    return 0;
  }

  // Call the target function
  char *response = redisCommand(c, format.c_str());

  if (response != NULL)
    freeReplyObject(response);

  redisFree(c);

  return 0;
}