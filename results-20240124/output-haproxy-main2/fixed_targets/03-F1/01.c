#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(stream.ConsumeRemainingBytesAsString());
  }
  char** argv_ptr = new char*[argc];
  for (int i = 0; i < argc; i++) {
    argv_ptr[i] = const_cast<char*>(argv[i].c_str());
  }
  main(argc, argv_ptr);
  delete[] argv_ptr;
  return 0;
}