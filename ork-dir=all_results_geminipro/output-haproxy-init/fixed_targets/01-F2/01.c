#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <unistd.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int argc = provider.ConsumeIntegralInRange<int>(0, 100);
  std::vector<char*> argv;

  for (int i = 0; i < argc; i++) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    auto arg = provider.ConsumeBytes<char>(arg_size);
    argv.push_back(reinterpret_cast<char*>(arg.data()));
  }

  // Added the necessary header file `unistd.h` and wrapped it with `extern "C" {}` to resolve the undefined reference to `init` function.
  extern "C" void init(int argc, char** argv);
  init(argc, argv.data());

  return 0;
}