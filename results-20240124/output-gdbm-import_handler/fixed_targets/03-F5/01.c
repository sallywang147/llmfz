#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "command.h"

extern "C" {
#include "gdbm.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct command_param param;
  param.param_str = stream.ConsumeRemainingBytesAsString().c_str();

  struct command_environ cenv;
  cenv.ce_cmd_name = stream.ConsumeRemainingBytesAsString().c_str();

  import_handler(&param, &cenv);
  return 0;
}