#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "import_handler.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string command = stream.ConsumeRandomLengthString();
  std::string command_arg = stream.ConsumeRandomLengthString();
  std::string command_arg2 = stream.ConsumeRandomLengthString();

  struct command_param param;
  param.param_name = const_cast<char*>(command.c_str());
  param.param_arg = const_cast<char*>(command_arg.c_str());
  param.param_arg2 = const_cast<char*>(command_arg2.c_str());

  struct command_environ cenv;
  cenv.cenv_cwd = const_cast<char*>("/");

  import_handler(&param, &cenv);
  return 0;
}