#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "mutate.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for the function mutate
  struct param p;
  int seed = stream.ConsumeIntegral<int>();
  int flags = stream.ConsumeIntegral<int>();

  // Call the function mutate
  mutate(&p, seed, flags);

  return 0;
}