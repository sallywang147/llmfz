#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <getopt.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int argc = provider.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
    auto arg = provider.ConsumeBytes<char>(arg_size);
    argv.push_back(reinterpret_cast<char*>(arg.data()));
  }
  init(argc, argv.data());
  return 0;
}