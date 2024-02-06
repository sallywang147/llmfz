#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg1 = stream.ConsumeIntegral<int>();
  int int_arg2 = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Call the function under test
  struct DICT *result = dict_cidr_open(ptr, int_arg1, int_arg2);

  // Clean up
  if (result) {
    dict_close(result);
  }

  return 0;
}