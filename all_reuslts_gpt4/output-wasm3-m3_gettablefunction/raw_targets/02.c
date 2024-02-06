#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "m3_api_defs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  struct M3Function *func = nullptr;
  struct M3Module *mod = nullptr;
  int num = provider.ConsumeIntegral<int>();

  char * result = m3_GetTableFunction(&func, mod, num);

  return 0;
}