#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "wgnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const int bufsize = stream.ConsumeIntegralInRange<int>(1, 1024);
  char* buf = new char[bufsize];
  const std::string arg = stream.ConsumeRemainingBytesAsString();
  const double timeout = stream.ConsumeFloatingPoint<double>();
  int ret = wgnutls_read_timeout(fd, buf, bufsize, arg.c_str(), timeout);
  delete[] buf;
  return ret;
}