#include <fuzzer/FuzzedDataProvider.h>
#include <hiredis/async.h>
#include <hiredis/hiredis.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a dummy async context
  redisAsyncContext ac;
  ac.err = 0;
  ac.errstr = NULL;
  ac.data = NULL;
  ac.c.flags = REDIS_CONNECTED;
  ac.c.fd = stream.ConsumeIntegral<int>();
  ac.c.sndbuf = stream.ConsumeIntegral<size_t>();
  ac.c.rcvbuf = stream.ConsumeBytes<char>(stream.remaining_bytes());

  // Call the function under test
  redisAsyncRead(&ac);

  return 0;
}