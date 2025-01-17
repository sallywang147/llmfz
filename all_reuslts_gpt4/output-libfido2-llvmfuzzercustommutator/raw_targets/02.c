#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t LLVMFuzzerCustomMutator(char * data, size_t size, size_t maxsize, int seed);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  size_t size_arg = stream.ConsumeIntegral<size_t>();
  size_t maxsize_arg = stream.ConsumeIntegral<size_t>();
  int seed_arg = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeBytesAsString(stream.remaining_bytes());
  char *data_arg = const_cast<char*>(str.c_str());

  // Call the target function
  LLVMFuzzerCustomMutator(data_arg, size_arg, maxsize_arg, seed_arg);

  return 0;
}