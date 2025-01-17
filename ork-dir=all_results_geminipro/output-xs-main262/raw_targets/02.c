#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t argc = provider.ConsumeIntegralInRange<size_t>(1, 100);
  std::vector<char*> argv;
  for (size_t i = 0; i < argc; i++) {
    const size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 1000);
    std::vector<char> arg_data = provider.ConsumeBytes<char>(arg_size);
    arg_data.push_back('\0');
    argv.push_back(arg_data.data());
  }
  main262(argc, argv.data());
  return 0;
}