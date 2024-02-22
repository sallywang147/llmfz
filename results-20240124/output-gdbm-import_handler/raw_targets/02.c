 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t command_param_count = stream.ConsumeIntegral<uint8_t>();
  std::vector<std::string> command_param_list;
  for (uint8_t i = 0; i < command_param_count; ++i) {
    command_param_list.push_back(stream.ConsumeRemainingBytesAsString());
  }
  const std::string command_environ_param =
      stream.ConsumeRemainingBytesAsString();

  struct command_param param;
  param.param_list = command_param_list;
  struct command_environ cenv;
  cenv.param = command_environ_param;

  import_handler(&param, &cenv);

  return 0;
}