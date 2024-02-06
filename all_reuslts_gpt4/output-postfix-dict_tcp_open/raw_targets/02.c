#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the first parameter.
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Extract integral values for the second and third parameters.
  int int_arg1 = stream.ConsumeIntegral<int>();
  int int_arg2 = stream.ConsumeIntegral<int>();

  // Call the function to fuzz.
  struct DICT *dict = dict_tcp_open(ptr, int_arg1, int_arg2);

  // Clean up.
  if (dict != NULL) {
    dict_close(dict);
  }

  return 0;
}