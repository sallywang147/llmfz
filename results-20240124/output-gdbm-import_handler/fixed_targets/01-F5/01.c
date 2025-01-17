#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "command.h"
#include "command_param.h"
#include "command_environ.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct command_param param;
  struct command_environ cenv;
  param.param_name = stream.ConsumeRemainingBytesAsString().c_str();
  cenv.cenv_name = stream.ConsumeRemainingBytesAsString().c_str();
  import_handler(&param, &cenv);
  return 0;
}