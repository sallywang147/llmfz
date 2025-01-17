#include <fuzzer/FuzzedDataProvider.h>
#include "hiredis.h"
#include "async.h"
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();

  int fds[2];
  if (pipe(fds) != 0) {
    return 0;
  }

  write(fds[1], str.data(), str.size());
  close(fds[1]);

  redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac->err) {
    close(fds[0]);
    return 0;
  }

  ac->c.fd = fds[0];
  redisAsyncRead(ac);

  close(fds[0]);
  redisAsyncFree(ac);

  return 0;
}