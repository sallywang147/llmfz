#include <fuzzer/FuzzedDataProvider.h>
#include "hiredis/async.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize redisAsyncContext with dummy values
  redisAsyncContext ac;
  ac.c.flags = REDIS_CONNECTED;
  ac.c.fd = stream.ConsumeIntegral<int>();
  ac.c.sndbuf = stream.ConsumeIntegral<int>();
  ac.c.rcvbuf = stream.ConsumeIntegral<int>();

  // Call the target function
  redisProcessCallbacks(&ac);

  return 0;
}