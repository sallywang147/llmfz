#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(const_cast<char*>(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str()));
  }
  const char* envp = stream.ConsumeRemainingBytesAsString().c_str();

  // Fix: include the necessary header file for 'cmd_am'
  #include "cmd_am.h"

  cmd_am(argc, argv.data(), const_cast<char*>(envp));
  return 0;
}