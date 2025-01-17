 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "command_param.h"
#include "command_environ.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct command_param param;
  struct command_environ cenv;

  param.param_type = provider.ConsumeIntegral<enum param_type>();
  param.param_string = provider.ConsumeBytesAsString();
  param.param_int = provider.ConsumeIntegral<int>();
  param.param_int64 = provider.ConsumeIntegral<int64_t>();
  param.param_bool = provider.ConsumeBool();
  param.param_array_size = provider.ConsumeIntegral<size_t>();
  param.param_array = provider.ConsumeBytes<uint8_t>(param.param_array_size);

  cenv.cenv_name = provider.ConsumeBytesAsString();
  cenv.cenv_value = provider.ConsumeBytesAsString();

  recover_handler(&param, &cenv);

  return 0;
}