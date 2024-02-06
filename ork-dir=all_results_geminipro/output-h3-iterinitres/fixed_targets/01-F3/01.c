#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" {
#include "iter.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  struct IterCellsResolution res;
  int arg_0 = provider.ConsumeIntegral<int>();
  iterInitRes(&res, arg_0);
  return 0;
}