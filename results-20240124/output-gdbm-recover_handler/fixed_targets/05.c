#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "command.h"
#include "command_param.h"
#include "command_environ.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct command_param* param = new struct command_param;
  param->param_name = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  param->param_value = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  struct command_environ* cenv = new struct command_environ;
  cenv->cenv_argc = provider.ConsumeIntegral<int>();
  cenv->cenv_argv = new char*[cenv->cenv_argc];
  for (int i = 0; i < cenv->cenv_argc; i++) {
    cenv->cenv_argv[i] = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(0, 100)).c_str();
  }

  recover_handler(param, cenv);

  delete[] cenv->cenv_argv;
  delete cenv;
  delete param;

  return 0;
}