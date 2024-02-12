 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tpm_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int argc = provider.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    size_t arg_len = provider.ConsumeIntegralInRange<size_t>(0, size);
    auto arg_data = provider.ConsumeBytes<char>(arg_len);
    argv.push_back(strdup(arg_data.data()));
  }

  tpm_server_main(argc, argv.data());

  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }

  return 0;
}