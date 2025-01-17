#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t argc = stream.ConsumeIntegralInRange<size_t>(1, 10);
  std::vector<char*> argv(argc);
  for (size_t i = 0; i < argc; ++i) {
    const size_t arg_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
    std::string arg = stream.ConsumeRandomLengthString(arg_len);
    argv[i] = strdup(arg.c_str());
  }

  const size_t cmd_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::string cmd = stream.ConsumeRandomLengthString(cmd_len);

  cmd_rebase(argc, argv.data(), const_cast<char*>(cmd.c_str()));

  for (size_t i = 0; i < argc; ++i) {
    free(argv[i]);
  }

  return 0;
}