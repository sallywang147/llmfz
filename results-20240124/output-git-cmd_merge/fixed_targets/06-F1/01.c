#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(const_cast<char*>(stream.ConsumeRemainingBytesAsString().c_str()));
  }
  char* envp = nullptr;
  cmd_merge(argc, argv.data(), envp);
  return 0;
}