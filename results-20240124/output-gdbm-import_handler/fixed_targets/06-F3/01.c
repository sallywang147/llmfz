#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "command.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct command_param param;
  struct command_environ cenv;
  param.param_str = provider.ConsumeRemainingBytesAsString().c_str();
  return import_handler(&param, &cenv);
}