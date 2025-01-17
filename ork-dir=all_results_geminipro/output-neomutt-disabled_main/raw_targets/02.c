#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int argc = provider.ConsumeIntegralInRange<int>(0, 10);
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
    auto arg = provider.ConsumeBytes<char>(arg_size);
    argv.push_back(reinterpret_cast<char*>(arg.data()));
  }
  std::vector<char*> envp;
  int envp_size = provider.ConsumeIntegralInRange<int>(0, 10);
  for (int i = 0; i < envp_size; i++) {
    size_t env_size = provider.ConsumeIntegralInRange<size_t>(0, 100);
    auto env = provider.ConsumeBytes<char>(env_size);
    envp.push_back(reinterpret_cast<char*>(env.data()));
  }
  disabled_main(argc, argv.data(), envp.data());
  return 0;
}