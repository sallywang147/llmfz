 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t num_args = stream.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<std::string> args(num_args);
  for (size_t i = 0; i < num_args; i++) {
    args[i] = stream.ConsumeRemainingBytesAsString();
  }

  std::vector<char*> c_args;
  c_args.reserve(num_args + 1);
  for (const std::string& arg : args) {
    c_args.push_back(const_cast<char*>(arg.c_str()));
  }
  c_args.push_back(nullptr);

  cmd_am(num_args, c_args.data(), nullptr);
  return 0;
}