 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "command.h"
#include "command_environ.h"
#include "command_param.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct command_param param = {
    .type = stream.ConsumeIntegral<command_param_type_t>(),
    .str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100)).c_str(),
    .num = stream.ConsumeIntegral<int64_t>(),
    .flag = stream.ConsumeBool(),
  };

  struct command_environ cenv = {
    .argc = stream.ConsumeIntegral<int>(),
    .argv = stream.ConsumeRemainingBytesAsString().c_str(),
  };

  recover_handler(&param, &cenv);

  return 0;
}