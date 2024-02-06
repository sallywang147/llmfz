#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <poll.h>

extern "C" void after_poll(struct pollfd * pfd, size_t npfd, int maxfds);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t npfd = stream.ConsumeIntegralInRange<size_t>(1, 100);
  std::vector<struct pollfd> pfd(npfd);

  for (size_t i = 0; i < npfd; ++i) {
    pfd[i].fd = stream.ConsumeIntegral<int>();
    pfd[i].events = stream.ConsumeIntegral<short>();
    pfd[i].revents = stream.ConsumeIntegral<short>();
  }

  int maxfds = stream.ConsumeIntegral<int>();

  after_poll(pfd.data(), npfd, maxfds);

  return 0;
}