 #include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    std::string arg = stream.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  main2(argc, argv.data());
  return 0;
}