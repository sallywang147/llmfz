#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "wgnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const int bufsize = stream.ConsumeIntegralInRange<int>(0, 1 << 16);
  char* buf = new char[bufsize];
  const int arg_size = stream.ConsumeIntegralInRange<int>(0, 1 << 16);
  char* arg = new char[arg_size];
  const double timeout = stream.ConsumeFloatingPoint<double>();

  wgnutls_read_timeout(fd, buf, bufsize, arg, arg_size, timeout);

  delete[] buf;
  delete[] arg;

  return 0;
}