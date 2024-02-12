#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "fuzzer/FuzzedDataProvider.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t arg_count = stream.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<std::string> args;
  for (size_t i = 0; i < arg_count; ++i) {
    args.push_back(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)));
  }
  main2(arg_count, args.data());
  return 0;
}