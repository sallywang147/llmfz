#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <string>

#include "poll.h"

extern "C" {
#include "poll.h"
}

int run_poll_loop(struct pollfd *fds, nfds_t nfds, int timeout);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int timeout = stream.ConsumeIntegral<int>();
  const int nfds = stream.ConsumeIntegral<int>();
  struct pollfd fds[nfds];
  for (int i = 0; i < nfds; i++) {
    fds[i].fd = stream.ConsumeIntegral<int>();
    fds[i].events = stream.ConsumeIntegral<short>();
    fds[i].revents = 0;
  }
  run_poll_loop(fds, nfds, timeout);
  return 0;
}

int run_poll_loop(struct pollfd *fds, nfds_t nfds, int timeout) {
  return poll(fds, nfds, timeout);
}