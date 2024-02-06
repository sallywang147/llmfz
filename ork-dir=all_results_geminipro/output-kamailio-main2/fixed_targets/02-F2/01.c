#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int argc = provider.ConsumeIntegralInRange<int>(0, 10);
  std::vector<char*> argv(argc);
  for (int i = 0; i < argc; ++i) {
    size_t len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    argv[i] = new char[len + 1];
    provider.ConsumeBytes<char>(argv[i], len);
    argv[i][len] = '\0';
  }

  int ret = main2(argc, argv.data());

  for (int i = 0; i < argc; ++i) {
    delete[] argv[i];
  }

  return ret;
}