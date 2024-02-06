#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Extract values from the fuzzed input
  std::string str = provider.ConsumeRandomLengthString();
  int arg1 = provider.ConsumeIntegral<int>();
  int arg2 = provider.ConsumeIntegral<int>();

  // Call the function with the extracted values
  struct DICT * dict = dict_cidr_open(const_cast<char*>(str.c_str()), arg1, arg2);

  // Cleanup
  if (dict != nullptr) {
    dict_close(dict);
  }

  return 0;
}