 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int argc = provider.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    const std::string arg = provider.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  main2(argc, argv.data());
  return 0;
}