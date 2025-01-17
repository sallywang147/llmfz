#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "wgnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const size_t bufsize = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char* buf = new char[bufsize];
  const std::string arg = stream.ConsumeRemainingBytesAsString();
  const double timeout = stream.ConsumeFloatingPoint<double>();

  int ret = wgnutls_read(fd, buf, bufsize, const_cast<char*>(arg.c_str()), timeout);
  delete[] buf;
  return ret;
}