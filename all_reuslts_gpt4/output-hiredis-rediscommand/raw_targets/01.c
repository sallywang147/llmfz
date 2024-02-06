#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a Redis context
  struct redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL || c->err) {
    if (c) {
      redisFree(c);
    }
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string format = stream.ConsumeRemainingBytesAsString();
  char *format_ptr = strdup(format.c_str());

  // Call the target function
  char *response = redisCommand(c, format_ptr);

  // Free the memory
  freeReplyObject(response);
  free(format_ptr);
  redisFree(c);

  return 0;
}