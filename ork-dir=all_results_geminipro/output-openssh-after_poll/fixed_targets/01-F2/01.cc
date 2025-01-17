#include <fuzzer/FuzzedDataProvider.h>
#include <poll.h>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_pollfd = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<pollfd> pollfd_vector(num_pollfd);

  for (size_t i = 0; i < num_pollfd; i++) {
    pollfd_vector[i].fd = stream.ConsumeIntegral<int>();
    pollfd_vector[i].events = stream.ConsumeIntegral<short>();
    pollfd_vector[i].revents = 0;
  }

  const int maxfds = stream.ConsumeIntegral<int>();
  poll(pollfd_vector.data(), num_pollfd, maxfds);
  after_poll(pollfd_vector.data(), num_pollfd, maxfds);
  return 0;
}