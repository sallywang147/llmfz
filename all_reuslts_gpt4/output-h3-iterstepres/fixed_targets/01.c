#include <fuzzer/FuzzedDataProvider.h>
#include "h3api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the struct
  struct IterCellsResolution itR;
  itR.h = stream.ConsumeIntegral<H3Index>();
  itR.center = stream.ConsumeIntegral<H3Index>();
  itR.resolution = stream.ConsumeIntegral<int>();
  itR.distance = stream.ConsumeIntegral<int>();
  itR.numHexes = stream.ConsumeIntegral<int>();

  // Call the function with the fuzzed input
  iterStepRes(&itR);

  return 0;
}