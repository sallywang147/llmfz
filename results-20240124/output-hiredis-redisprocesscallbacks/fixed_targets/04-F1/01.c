#include <hiredis.h>
#include <iostream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL || ac->err) {
    if (ac) {
      std::cerr << "Error: " << ac->errstr << std::endl;
      redisAsyncFree(ac);
    } else {
      std::cerr << "Error: Can't allocate redis context" << std::endl;
    }
    return 0;
  }
  redisProcessCallbacks(ac);
  redisAsyncFree(ac);
  return 0;
}