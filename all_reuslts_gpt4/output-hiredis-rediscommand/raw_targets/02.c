#include "hiredis.h"
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Create a new Redis context
  redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL || c->err) {
    if (c) {
      redisFree(c);
    }
    return 0;
  }

  // Extract a string from the data provider
  std::string format = stream.ConsumeRandomLengthString();
  char *format_cstr = strdup(format.c_str());

  // Call the target function
  char *response = redisCommand(c, format_cstr);

  // Cleanup
  free(format_cstr);
  freeReplyObject(response);
  redisFree(c);

  return 0;
}