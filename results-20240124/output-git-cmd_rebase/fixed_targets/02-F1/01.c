#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  const std::string command = stream.ConsumeRemainingBytesAsString();
  cmd_rebase(argc, argv.data(), const_cast<char*>(command.c_str()));
  return 0;
}