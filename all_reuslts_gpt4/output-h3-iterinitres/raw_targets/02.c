#include <fuzzer/FuzzedDataProvider.h>
#include "h3api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  IterCellsResolution res;
  int k = stream.ConsumeIntegral<int>();
  
  iterInitRes(&res, k);
  
  return 0;
}