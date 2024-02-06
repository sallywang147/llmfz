#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;  // Not enough data to do anything meaningful.
  }

  FuzzedDataProvider stream(data, size);

  // Extract the first two bytes to use as our flags.
  int flag1 = stream.ConsumeIntegral<int>();
  int flag2 = stream.ConsumeIntegral<int>();

  // Use the remaining bytes as our string.
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = const_cast<char*>(str.c_str());

  // Call the target function.
  struct DICT* dict = dict_regexp_open(ptr, flag1, flag2);

  // Clean up.
  if (dict != nullptr) {
    dict_close(dict);
  }

  return 0;
}