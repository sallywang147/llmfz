#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include <poll.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<struct pollfd> pfd_vector;
  size_t npfd = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  for (size_t i = 0; i < npfd; i++) {
    struct pollfd pfd;
    pfd.fd = stream.ConsumeIntegral<int>();
    pfd.events = stream.ConsumeIntegral<short>();
    pfd.revents = 0;
    pfd_vector.push_back(pfd);
  }

  int maxfds = stream.ConsumeIntegralInRange<int>(0, 1000);

  poll(pfd_vector.data(), npfd, maxfds);

  return 0;
}