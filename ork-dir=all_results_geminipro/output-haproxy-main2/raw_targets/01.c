#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<char*> argv_vector;
  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    auto arg = provider.ConsumeBytes<char>(arg_size);
    argv_vector.push_back(arg.data());
  }
  argv_vector.push_back(nullptr);

  char** argv = argv_vector.data();
  int argc = argv_vector.size() - 1;

  main2(argc, argv);

  return 0;
}