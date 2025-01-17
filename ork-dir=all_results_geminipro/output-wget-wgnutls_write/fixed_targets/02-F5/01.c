#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "wgnutls.h"

extern "C" {
#include "wgnutls.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int fd = stream.ConsumeIntegral<int>();
  const size_t bufsize = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> buf(bufsize);
  stream.ConsumeBytes<char>(buf.data(), bufsize);

  const std::string arg = stream.ConsumeRemainingBytesAsString();

  wgnutls_write(fd, buf.data(), bufsize, arg.c_str());

  return 0;
}