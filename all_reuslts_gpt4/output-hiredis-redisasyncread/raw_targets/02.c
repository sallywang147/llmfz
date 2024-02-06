#include <fuzzer/FuzzedDataProvider.h>
#include <hiredis/async.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create an async context
  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac->err) {
    // Let *ac leak if the connection failed.
    return 0;
  }

  // Feed data to the async context
  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();
  ac->c.reader->buf = buffer.data();
  ac->c.reader->pos = 0;
  ac->c.reader->len = buffer.size();

  // Call the function to be fuzzed
  redisAsyncRead(ac);

  // Cleanup
  redisAsyncDisconnect(ac);

  return 0;
}