#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tmux.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tmuxproc_initialize(0);
    initialized = true;
  }
  FuzzedDataProvider provider(data, size);

  struct tmuxproc* client = nullptr;
  struct event_base* base = event_init();
  int flags = provider.ConsumeIntegral<int>();
  int lockfd = provider.ConsumeIntegral<int>();
  std::string lockfile = provider.ConsumeRandomLengthString();

  int ret = server_start(client, flags, base, lockfd, lockfile.c_str());
  if (ret != 0) {
    return 0;
  }

  event_base_loop(base, EVLOOP_NONBLOCK);
  server_stop(0);
  event_base_free(base);

  return 0;
}