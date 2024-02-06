#include "hiredis.h"
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);
  
  // Create a new redis context
  redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL || c->err) {
    if (c) {
      redisFree(c);
    }
    return 0;
  }

  // Extract a string from the stream
  std::string format = stream.ConsumeRemainingBytesAsString();
  
  // Create a va_list and pass it to the function
  va_list ap;
  va_start(ap, format.c_str());
  char *reply = redisvCommand(c, format.c_str(), ap);
  va_end(ap);

  // Free the reply if it's not NULL
  if (reply != NULL) {
    freeReplyObject(reply);
  }

  // Free the redis context
  redisFree(c);

  return 0;
}