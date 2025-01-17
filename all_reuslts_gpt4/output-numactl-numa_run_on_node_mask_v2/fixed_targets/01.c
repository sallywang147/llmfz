#include "numa.h"
#include <stdint.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a bitmask from the fuzzed data
  struct bitmask *mask = numa_allocate_nodemask();
  for (size_t i = 0; i < mask->size && stream.remaining_bytes() > 0; i++) {
    if (stream.ConsumeBool()) {
      numa_bitmask_setbit(mask, i);
    }
  }

  // Call the function under test
  numa_run_on_node_mask_v2(mask);

  // Clean up
  numa_bitmask_free(mask);

  return 0;
}