#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "command.h"

extern "C" {
#include "recover_handler.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct command_param param;
  memset(&param, 0, sizeof(param));

  struct command_environ cenv;
  memset(&cenv, 0, sizeof(cenv));

  recover_handler(&param, &cenv, stream.ConsumeRemainingBytesAsString().c_str());

  return 0;
}