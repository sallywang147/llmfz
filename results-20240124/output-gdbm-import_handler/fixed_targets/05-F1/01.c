#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "command.h"
#include "command_param.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct command_param param;
  struct command_environ cenv;
  param.param_string = stream.ConsumeRemainingBytesAsString().c_str();
  import_handler(&param, &cenv);
  return 0;
}