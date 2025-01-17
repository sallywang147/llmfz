#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t argc = stream.ConsumeIntegralInRange<size_t>(1, 100);
  std::vector<std::string> argv;
  for (size_t i = 0; i < argc; i++) {
    argv.push_back(stream.ConsumeRemainingBytesAsString());
  }

  char** argv_ptr = new char*[argc];
  for (size_t i = 0; i < argc; i++) {
    argv_ptr[i] = const_cast<char*>(argv[i].c_str());
  }

  int omain_ret = omain(static_cast<int>(argc), argv_ptr);

  delete[] argv_ptr;
  return omain_ret;
}