#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "mworker.h"

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  mworker_loop(fd);
  return 0;
}