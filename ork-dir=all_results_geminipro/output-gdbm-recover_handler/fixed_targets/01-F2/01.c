#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "command.h"

extern "C" {
#include "recover_handler.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct command_param param;
  std::string param_str = stream.ConsumeRemainingBytesAsString();
  param.arg = reinterpret_cast<uint8_t*>(const_cast<char*>(param_str.c_str()));
  param.arg_len = param_str.length();

  struct command_environ cenv;
  recover_handler(&param, &cenv);
  return 0;
}