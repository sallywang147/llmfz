#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "xopendirat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int fd = stream.ConsumeIntegral<int>();
  std::string name = stream.ConsumeRandomLengthString();
  int flags = stream.ConsumeIntegral<int>();
  struct __dirstream *ret = nullptr;

  xopendirat(fd, const_cast<char*>(name.c_str()), flags, &ret);

  return 0;
}