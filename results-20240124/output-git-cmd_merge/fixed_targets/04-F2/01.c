#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>  // for std::sort
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

extern "C" {
#include "cmd_merge.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(strdup(arg.c_str()));
  }
  std::string cmd = stream.ConsumeRemainingBytesAsString();
  std::sort(argv.begin(), argv.end());  // sort the arguments
  cmd_merge(argc, argv.data(), cmd.c_str());
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  return 0;
}