#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "lwan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lwan l;
  struct lwan_thread thread;

  // Initialize the lwan struct
  l.config.thread.max_fd = stream.ConsumeIntegral<unsigned int>();
  l.config.thread.max_clients = stream.ConsumeIntegral<unsigned int>();
  l.config.thread.timeout = stream.ConsumeIntegral<unsigned int>();
  l.config.thread.poll_backend = stream.ConsumeEnum<lwan_config_thread_poll_backend_t>();
  l.config.thread.flags = stream.ConsumeEnum<lwan_config_thread_flags_t>();

  // Initialize the lwan_thread struct
  thread.l = &l;
  thread.id = stream.ConsumeIntegral<unsigned int>();

  // Call the function to be fuzzed
  create_thread(&l, &thread);

  return 0;
}