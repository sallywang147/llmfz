#include <fuzzer/FuzzedDataProvider.h>
#include <numa.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Create a nodemask and initialize it with the fuzzed data
  struct nodemask_t nodemask;
  for (int i = 0; i < NUMA_NUM_NODES; i++) {
    if (stream.remaining_bytes() > 0) {
      nodemask.n[i] = stream.ConsumeIntegral<unsigned long>();
    } else {
      nodemask.n[i] = 0;
    }
  }

  // Call the function under test
  numa_bind_v1(&nodemask);

  return 0;
}