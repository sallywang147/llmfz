#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <wgnutls/wgnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const int bufsize = stream.ConsumeIntegralInRange<int>(1, 1024);
  char* buf = new char[bufsize];
  const int argsize = stream.ConsumeIntegralInRange<int>(1, 1024);
  char* arg = new char[argsize];
  const double timeout = stream.ConsumeFloatingPoint<double>();

  wgnutls_peek(fd, buf, bufsize, arg, timeout);

  delete[] buf;
  delete[] arg;
  return 0;
}