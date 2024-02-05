#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hiredis.h"
#include "async.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create the async context
  redisAsyncContext* ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac->err) {
    // Let's not fuzz when we can't connect to Redis
    return 0;
  }

  // Consume data from the fuzzer input
  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();
  buffer.push_back('\0');

  // Set up the buffer in the async context
  ac->c.reader->buf = buffer.data();

  // Call the function under test
  redisAsyncRead(ac);

  // Cleanup
  redisAsyncDisconnect(ac);

  return 0;
}