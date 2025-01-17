#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "thread_io.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t len = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  char* str = new char[len + 1];
  provider.ConsumeBytes(str, len);
  str[len] = '\0';
  thread_io_loop(str);
  delete[] str;
  return 0;
}