#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate argc and argv.
  const size_t argc = provider.ConsumeIntegralInRange<size_t>(1, 10);
  std::vector<char*> argv(argc);
  for (size_t i = 0; i < argc; ++i) {
    const size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 50);
    const std::string arg_str = provider.ConsumeRandomLengthString(arg_size);
    argv[i] = new char[arg_str.size() + 1];
    strcpy(argv[i], arg_str.c_str());
  }

  // Call omain.
  int ret = omain(argc, argv.data());

  // Free argv.
  for (size_t i = 0; i < argc; ++i) {
    delete[] argv[i];
  }

  return ret;
}