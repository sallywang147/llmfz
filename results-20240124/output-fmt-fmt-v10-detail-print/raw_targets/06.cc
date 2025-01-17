 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <string>
#include <cstdio>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  fmt::detail::print(stdout, const_cast<char*>(str.c_str()), str.size());
  return 0;
}