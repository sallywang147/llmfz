#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string format_str = provider.ConsumeRemainingBytesAsString();
  std::vector<fmt::format_arg> args;
  while (provider.remaining_bytes() > 0) {
    args.push_back(fmt::format(provider.ConsumeRemainingBytesAsString()));
  }

  FILE* f = fopen("/dev/null", "w");
  fmt::vprint(f, format_str.c_str(), args.data(), args.size());
  fclose(f);
  return 0;
}