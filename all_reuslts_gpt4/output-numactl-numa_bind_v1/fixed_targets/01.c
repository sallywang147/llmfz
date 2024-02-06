#include <fuzzer/FuzzedDataProvider.h>
#include "numa.h"
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  struct nodemask_t nodemask;
  for (size_t i = 0; i < sizeof(nodemask.n); i++) {
    nodemask.n[i] = stream.ConsumeIntegral<unsigned long>();
  }

  numa_bind_v1(&nodemask);
  return 0;
}