#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t argc = stream.ConsumeIntegralInRange<uint8_t>(1, 10);
  std::vector<std::string> argv;
  argv.reserve(argc);
  for (uint8_t i = 0; i < argc; ++i) {
    argv.push_back(stream.ConsumeRemainingBytesAsString());
  }

  char** argv_ptr = new char*[argc + 1];
  for (uint8_t i = 0; i < argc; ++i) {
    argv_ptr[i] = const_cast<char*>(argv[i].c_str());
  }
  argv_ptr[argc] = nullptr;

  int main2_ret = main2(argc, argv_ptr);
  delete[] argv_ptr;
  return main2_ret;
}