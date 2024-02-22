#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mworker.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  mworker_loop();
  return 0;
}