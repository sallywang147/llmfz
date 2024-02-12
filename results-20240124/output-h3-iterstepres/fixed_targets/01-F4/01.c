#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "iter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct IterCellsResolution itR;
  itR.cell = stream.ConsumeIntegral<uint64_t>();
  itR.level = stream.ConsumeIntegral<int>();
  itR.res = stream.ConsumeIntegral<int>();
  itR.res_prev = stream.ConsumeIntegral<int>();
  itR.res_next = stream.ConsumeIntegral<int>();

  iterStepRes(&itR);
  return 0;
}