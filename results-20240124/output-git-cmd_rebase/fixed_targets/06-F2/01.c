#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t argc = stream.ConsumeIntegral<size_t>();
  std::vector<char*> argv;
  for (size_t i = 0; i < argc; i++) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  const std::string env = stream.ConsumeRemainingBytesAsString();
  char* envp[] = {const_cast<char*>(env.c_str()), nullptr};

  // Fix: Include the necessary header file for the missing function.
  #include "cmd_rebase.h"

  cmd_rebase(argc, argv.data(), envp[0]);

  return 0;
}