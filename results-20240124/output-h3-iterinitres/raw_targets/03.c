 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "iter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct IterCellsResolution res;
  const int resolution = stream.ConsumeIntegral<int>();
  iterInitRes(&res, resolution);
  return 0;
}