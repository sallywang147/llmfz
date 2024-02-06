#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "command.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct command_param param = {0};
  struct command_environ cenv = {0};
  param.param = (char*)stream.ConsumeRemainingBytesAsString().c_str();

  import_handler(&param, &cenv);
  return 0;
}