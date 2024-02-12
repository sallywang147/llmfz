#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "command.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct command_param param;
  param.param_type = provider.ConsumeIntegral<int>();
  param.param_val = provider.ConsumeIntegral<int>();
  struct command_environ cenv;
  recover_handler(&param, &cenv);
  return 0;
}