#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tor_main.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create and initialize a tor_main_configuration_t object
  struct tor_main_configuration_t tor_cfg;
  tor_cfg.argc = 0;
  tor_cfg.argv = nullptr;

  // Consume data from the fuzzer input
  int argc = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<char*> argv(argc + 1, nullptr);

  for (int i = 0; i < argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv[i] = strdup(arg.c_str());
  }

  // Set the argc and argv in tor_cfg
  tor_cfg.argc = argc;
  tor_cfg.argv = argv.data();

  // Call the function to fuzz
  tor_run_main(&tor_cfg);

  // Cleanup
  for (auto arg : argv) {
    free(arg);
  }

  return 0;
}