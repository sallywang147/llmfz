#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int wgnutls_peek(int fd, char * buf, int bufsize, char * arg, double timeout);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // We don't have a real file descriptor to work with, so we'll use a random one.
  int fd = provider.ConsumeIntegral<int>();

  // Consume a portion of the data for the buffer.
  size_t bufsize = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  std::string buf = provider.ConsumeBytesAsString(bufsize);
  
  // Consume another portion of the data for the arg.
  size_t argSize = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  std::string arg = provider.ConsumeBytesAsString(argSize);

  // Consume the rest of the data for the timeout.
  double timeout = provider.ConsumeFloatingPoint<double>();

  // Call the function under test.
  wgnutls_peek(fd, const_cast<char*>(buf.c_str()), bufsize, const_cast<char*>(arg.c_str()), timeout);

  return 0;
}