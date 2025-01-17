#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "command.h" // Assuming this is the header file where the import_handler function is declared.

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct command_param param;
  struct command_environ cenv;

  // Assuming that command_param and command_environ structures have the following fields for simplicity.
  param.argc = stream.ConsumeIntegral<int>();
  param.argv = new char*[param.argc];
  for (int i = 0; i < param.argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    param.argv[i] = strdup(arg.c_str());
  }

  cenv.envc = stream.ConsumeIntegral<int>();
  cenv.envp = new char*[cenv.envc];
  for (int i = 0; i < cenv.envc; ++i) {
    std::string env = stream.ConsumeRandomLengthString();
    cenv.envp[i] = strdup(env.c_str());
  }

  import_handler(&param, &cenv);

  // Free memory
  for (int i = 0; i < param.argc; ++i) {
    delete[] param.argv[i];
  }
  delete[] param.argv;

  for (int i = 0; i < cenv.envc; ++i) {
    delete[] cenv.envp[i];
  }
  delete[] cenv.envp;

  return 0;
}