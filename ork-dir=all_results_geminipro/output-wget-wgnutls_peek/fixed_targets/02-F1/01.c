#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "wgnutls.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int fd = stream.ConsumeIntegral<int>();
  const int bufsize = stream.ConsumeIntegral<int>();
  char* buf = new char[bufsize];
  const std::string arg = stream.ConsumeRemainingBytesAsString();
  const double timeout = stream.ConsumeFloatingPoint<double>();

  const int result = wgnutls_peek(fd, buf, bufsize, const_cast<char*>(arg.c_str()), timeout);
  delete[] buf;
  return result;
}