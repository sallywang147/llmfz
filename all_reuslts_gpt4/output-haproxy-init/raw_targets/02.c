#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  int argc = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<char*> argv;
  
  for (int i = 0; i < argc; i++) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  
  argv.push_back(nullptr); // argv should be null-terminated
  init(argc, argv.data());
  
  return 0;
}