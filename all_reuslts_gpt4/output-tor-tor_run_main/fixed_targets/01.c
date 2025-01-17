#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tor_main.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct tor_main_configuration_t tor_cfg;
  tor_cfg.argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv_strings;
  std::vector<char*> argv;
  for (int i = 0; i < tor_cfg.argc; ++i) {
    argv_strings.push_back(stream.ConsumeRandomLengthString());
  }
  for (auto& str : argv_strings) {
    argv.push_back(const_cast<char*>(str.c_str()));
  }
  tor_cfg.argv = argv.data();

  tor_run_main(&tor_cfg);

  return 0;
}