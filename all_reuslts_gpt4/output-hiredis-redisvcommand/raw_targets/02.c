#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string format = stream.ConsumeRandomLengthString();

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

  va_list ap;
  va_start(ap, format.c_str());
  char *reply = redisvCommand(c, format.c_str(), ap);
  va_end(ap);

  if (reply != NULL) {
    free(reply);
  }

  redisFree(c);
  return 0;
}