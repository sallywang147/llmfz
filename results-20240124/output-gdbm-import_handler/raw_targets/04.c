 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* command = stream.ConsumeRandomLengthString();
  const char* command_arg = stream.ConsumeRandomLengthString();
  const char* command_arg2 = stream.ConsumeRandomLengthString();

  struct command_param param;
  param.param_name = const_cast<char*>(command);
  param.param_arg = const_cast<char*>(command_arg);
  param.param_arg2 = const_cast<char*>(command_arg2);

  struct command_environ cenv;
  cenv.cenv_cwd = const_cast<char*>("/");

  import_handler(&param, &cenv);
  return 0;
}