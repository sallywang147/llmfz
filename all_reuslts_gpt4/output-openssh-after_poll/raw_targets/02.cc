#include <fuzzer/FuzzedDataProvider.h>
#include <poll.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t npfd = stream.ConsumeIntegralInRange<size_t>(1, 1000);
  std::vector<struct pollfd> pfd(npfd);

  for (size_t i = 0; i < npfd; i++) {
    pfd[i].fd = stream.ConsumeIntegral<int>();
    pfd[i].events = stream.ConsumeIntegral<short>();
    pfd[i].revents = stream.ConsumeIntegral<short>();
  }

  const int maxfds = stream.ConsumeIntegral<int>();

  after_poll(pfd.data(), npfd, maxfds);

  return 0;
}