#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wgnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int fd = provider.ConsumeIntegral<int>();
  int bufsize = provider.ConsumeIntegralInRange<int>(1, 100);
  std::vector<char> buf(bufsize);
  std::string arg = provider.ConsumeRandomLengthString();
  double timeout = provider.ConsumeFloatingPoint<double>();

  wgnutls_read_timeout(fd, buf.data(), bufsize, arg.data(), timeout);

  return 0;
}