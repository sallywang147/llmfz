#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <string>
#include <vector>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t argc = stream.ConsumeIntegralInRange<size_t>(1, 10);
  std::vector<char*> argv;
  argv.push_back(strdup("./__XX"));
  for (size_t i = 0; i < argc - 1; ++i) {
    const size_t arg_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
    const std::string arg = stream.ConsumeBytesAsString(arg_size);
    argv.push_back(strdup(arg.c_str()));
  }
  const int result = __XX_main(argc, argv.data());
  for (size_t i = 0; i < argc; ++i) {
    free(argv[i]);
  }
  return result;
}