#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "command.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string command = stream.ConsumeRemainingBytesAsString();
  const std::string arg1 = stream.ConsumeRemainingBytesAsString();
  const std::string arg2 = stream.ConsumeRemainingBytesAsString();
  const std::string arg3 = stream.ConsumeRemainingBytesAsString();
  const std::string arg4 = stream.ConsumeRemainingBytesAsString();
  const std::string arg5 = stream.ConsumeRemainingBytesAsString();
  const std::string arg6 = stream.ConsumeRemainingBytesAsString();
  const std::string arg7 = stream.ConsumeRemainingBytesAsString();
  const std::string arg8 = stream.ConsumeRemainingBytesAsString();
  const std::string arg9 = stream.ConsumeRemainingBytesAsString();
  const std::string arg10 = stream.ConsumeRemainingBytesAsString();
  const std::string arg11 = stream.ConsumeRemainingBytesAsString();
  const std::string arg12 = stream.ConsumeRemainingBytesAsString();
  const std::string arg13 = stream.ConsumeRemainingBytesAsString();
  const std::string arg14 = stream.ConsumeRemainingBytesAsString();
  const std::string arg15 = stream.ConsumeRemainingBytesAsString();
  const std::string arg16 = stream.ConsumeRemainingBytesAsString();
  const std::string arg17 = stream.ConsumeRemainingBytesAsString();
  const std::string arg18 = stream.ConsumeRemainingBytesAsString();
  const std::string arg19 = stream.ConsumeRemainingBytesAsString();
  const std::string arg20 = stream.ConsumeRemainingBytesAsString();

  struct command_param param;
  param.cmd = command.c_str();
  param.arg[0] = arg1.c_str();
  param.arg[1] = arg2.c_str();
  param.arg[2] = arg3.c_str();
  param.arg[3] = arg4.c_str();
  param.arg[4] = arg5.c_str();
  param.arg[5] = arg6.c_str();
  param.arg[6] = arg7.c_str();
  param.arg[7] = arg8.c_str();
  param.arg[8] = arg9.c_str();
  param.arg[9] = arg10.c_str();
  param.arg[10] = arg11.c_str();
  param.arg[11] = arg12.c_str();
  param.arg[12] = arg13.c_str();
  param.arg[13] = arg14.c_str();
  param.arg[14] = arg15.c_str();
  param.arg[15] = arg16.c_str();
  param.arg[16] = arg17.c_str();
  param.arg[17] = arg18.c_str();
  param.arg[18] = arg19.c_str();
  param.arg[19] = arg20.c_str();

  struct command_environ cenv;
  recover_handler(&param, &cenv);
  return 0;
}