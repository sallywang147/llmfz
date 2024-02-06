#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "command_param.h"
#include "command_environ.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the command_param structure
  struct command_param param;
  param.argc = stream.ConsumeIntegral<int>();
  param.argv = new char*[param.argc];
  for (int i = 0; i < param.argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    param.argv[i] = new char[arg.size() + 1];
    std::strcpy(param.argv[i], arg.c_str());
  }

  // Initialize the command_environ structure
  struct command_environ cenv;
  cenv.envc = stream.ConsumeIntegral<int>();
  cenv.envv = new char*[cenv.envc];
  for (int i = 0; i < cenv.envc; ++i) {
    std::string env = stream.ConsumeRandomLengthString();
    cenv.envv[i] = new char[env.size() + 1];
    std::strcpy(cenv.envv[i], env.c_str());
  }

  // Call the function to be fuzzed
  int result = import_handler(&param, &cenv);

  // Clean up
  for (int i = 0; i < param.argc; ++i) {
    delete[] param.argv[i];
  }
  delete[] param.argv;

  for (int i = 0; i < cenv.envc; ++i) {
    delete[] cenv.envv[i];
  }
  delete[] cenv.envv;

  return 0;
}