#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "or/options.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  struct or_options_t old_options;
  char *msg = nullptr;

  // Initialize old_options with fuzzed data
  old_options.Magic = fuzzed_data.ConsumeIntegral<int>();
  old_options.config_line = fuzzed_data.ConsumeRandomLengthString().c_str();
  old_options.testSocks = fuzzed_data.ConsumeBool();
  old_options.RunAsDaemon = fuzzed_data.ConsumeBool();

  // Call the target function
  int result = options_act_reversible__real(&old_options, &msg);

  return 0;
}