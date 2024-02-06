#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include <wgnutls/wgnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const int fd = provider.ConsumeIntegral<int>();
  const size_t bufsize = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> buf(bufsize);
  const std::string arg = provider.ConsumeRemainingBytesAsString();
  const double timeout = provider.ConsumeFloatingPoint<double>();

  wgnutls_read(fd, buf.data(), bufsize, const_cast<char*>(arg.c_str()), timeout);
  return 0;
}