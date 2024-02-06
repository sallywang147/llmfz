#include <fuzzer/FuzzedDataProvider.h>
#include "hiredis.h"
#include "async.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a redisAsyncContext
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac->err) {
    redisAsyncFree(ac);
    return 0;
  }

  // Consume data to create a command
  std::string command = stream.ConsumeRandomLengthString();
  redisAsyncCommand(ac, NULL, NULL, command.c_str());

  // Call the function to be fuzzed
  redisProcessCallbacks(ac);

  // Cleanup
  redisAsyncFree(ac);

  return 0;
}