#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int argc = provider.ConsumeIntegral<int>();
  if (argc < 0) {
    return 0;
  }
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, size);
    std::string arg = provider.ConsumeRandomLengthString(arg_size);
    argv.push_back(strdup(arg.c_str()));
  }
  int ret = main_loop(argc, argv.data());
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  return ret;
}

int main_loop(int argc, char** argv) {
  // Your code here
  return 0;
}