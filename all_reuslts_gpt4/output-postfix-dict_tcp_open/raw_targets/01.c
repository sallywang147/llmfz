#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string str = provider.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  int arg2 = provider.ConsumeIntegral<int>();
  int arg3 = provider.ConsumeIntegral<int>();

  struct DICT *result = dict_tcp_open(ptr, arg2, arg3);

  if (result != nullptr) {
    dict_close(result);
  }

  return 0;
}