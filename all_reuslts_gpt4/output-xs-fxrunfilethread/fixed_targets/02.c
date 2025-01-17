#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" char * fxRunFileThread(char * it);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume the data as a string.
  std::string str = fuzzed_data.ConsumeRemainingBytesAsString();

  // Convert the string to a C-style string.
  char* cstr = const_cast<char*>(str.c_str());

  // Call the function under test.
  fxRunFileThread(cstr);

  return 0;
}