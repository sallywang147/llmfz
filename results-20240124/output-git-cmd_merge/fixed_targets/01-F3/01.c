#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include <sysexits.h>
#include <unistd.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string arg1 = stream.ConsumeRandomLengthString();
  const std::string arg2 = stream.ConsumeRandomLengthString();
  const std::string arg3 = stream.ConsumeRandomLengthString();
  std::vector<char*> argv = {const_cast<char*>(arg1.c_str()),
                             const_cast<char*>(arg2.c_str()),
                             const_cast<char*>(arg3.c_str())};
  execv("/usr/bin/cmd_merge", argv.data());
  return 0;
}