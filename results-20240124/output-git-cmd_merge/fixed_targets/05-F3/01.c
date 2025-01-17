#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "cmd_merge.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t num_args = stream.ConsumeIntegralInRange<size_t>(1, 10);
  std::vector<char*> args;
  args.reserve(num_args);
  for (size_t i = 0; i < num_args; ++i) {
    const size_t arg_len = stream.ConsumeIntegralInRange<size_t>(1, 100);
    std::string arg = stream.ConsumeBytesAsString(arg_len);
    args.push_back(strdup(arg.c_str()));
  }

  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* input_ptr = strdup(input.c_str());

  // Fix: Call the `cmd_merge` function
  cmd_merge(num_args, args.data(), input_ptr);

  for (char* arg : args) {
    free(arg);
  }
  free(input_ptr);

  return 0;
}