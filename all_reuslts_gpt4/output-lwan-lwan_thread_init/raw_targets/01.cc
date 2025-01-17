#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "lwan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lwan l;
  l.config.thread.max_fd = stream.ConsumeIntegral<int>();
  l.config.thread.min_fd = stream.ConsumeIntegral<int>();
  l.config.thread.timeout = stream.ConsumeIntegral<int>();
  l.config.thread.poll_backend = stream.ConsumeIntegral<int>();
  l.config.thread.flags = stream.ConsumeIntegral<int>();

  lwan_thread_init(&l);

  return 0;
}