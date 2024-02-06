#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());
  int arg1 = stream.ConsumeIntegral<int>();
  int arg2 = stream.ConsumeIntegral<int>();

  struct DICT *dict = dict_regexp_open(ptr, arg1, arg2);

  if (dict != nullptr) {
    dict_close(dict);
  }

  return 0;
}