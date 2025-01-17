 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "command.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<std::string> args;
  while (stream.remaining_bytes() > 0) {
    args.push_back(stream.ConsumeRemainingBytesAsString());
  }
  command_param param = {.args = args};
  command_environ cenv = {};
  recover_handler(&param, &cenv);
  return 0;
}