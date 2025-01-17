#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int wgnutls_peek(int fd, char * buf, int bufsize, char * arg, double timeout);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int fd = stream.ConsumeIntegral<int>();
  int bufsize = stream.ConsumeIntegralInRange<int>(0, 1000);
  std::vector<char> buf(bufsize);
  std::string arg = stream.ConsumeRandomLengthString();
  double timeout = stream.ConsumeFloatingPoint<double>();

  wgnutls_peek(fd, buf.data(), bufsize, const_cast<char*>(arg.c_str()), timeout);

  return 0;
}