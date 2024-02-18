#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "command_param.h"
#include "command_environ.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct command_param param;
  struct command_environ cenv;

  // Initialize command_param
  param.param1 = stream.ConsumeIntegral<int>();
  param.param2 = stream.ConsumeIntegral<int>();
  param.param3 = stream.ConsumeIntegral<int>();
  param.param4 = stream.ConsumeIntegral<int>();

  // Initialize command_environ
  cenv.env1 = stream.ConsumeIntegral<int>();
  cenv.env2 = stream.ConsumeIntegral<int>();
  cenv.env3 = stream.ConsumeIntegral<int>();
  cenv.env4 = stream.ConsumeIntegral<int>();

  // Call the target function
  recover_handler(&param, &cenv);

  return 0;
}