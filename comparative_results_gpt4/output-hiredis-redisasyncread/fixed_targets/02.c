#include <fuzzer/FuzzedDataProvider.h>
#include <hiredis/adapters/libevent.h>
#include <hiredis/async.h>
#include <event.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct event_base* base = event_base_new();
  if (!base) return 0;

  redisAsyncContext* ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac->err) {
    redisAsyncFree(ac);
    event_base_free(base);
    return 0;
  }

  redisLibeventAttach(ac, base);

  FuzzedDataProvider stream(data, size);
  std::string command = stream.ConsumeRandomLengthString();
  if (!command.empty()) {
    redisAsyncCommand(ac, NULL, NULL, command.c_str());
  }

  redisAsyncRead(ac);

  redisAsyncFree(ac);
  event_base_free(base);

  return 0;
}