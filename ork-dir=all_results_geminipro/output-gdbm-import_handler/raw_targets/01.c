#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "command.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct command_param param;
  param.param = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 1024));
  param.val = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 1024));

  struct command_environ cenv;
  cenv.cenv = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 1024));

  import_handler(&param, &cenv);

  return 0;
}