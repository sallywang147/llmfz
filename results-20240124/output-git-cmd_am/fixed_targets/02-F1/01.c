#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  const std::string env = stream.ConsumeRemainingBytesAsString();
  char* envp[] = {const_cast<char*>(env.c_str()), nullptr};

  // Fix: Call the intended function instead of the undeclared 'cmd_am'.
  cmd_am(argc, argv.data(), envp[0]);

  return 0;
}