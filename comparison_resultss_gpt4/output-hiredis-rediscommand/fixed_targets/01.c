#include "fuzzer/FuzzedDataProvider.h"
#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if(size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);
  std::string format = stream.ConsumeRandomLengthString();

  struct timeval timeout = { 1, 500000 }; // 1.5 seconds
  redisContext *c = redisConnectWithTimeout("127.0.0.1", 6379, timeout);
  if (c == NULL || c->err) {
    if (c) {
      redisFree(c);
    }
    return 0;
  }

  char * response = redisCommand(c, format.c_str());
  free(response);
  redisFree(c);
  
  return 0;
}