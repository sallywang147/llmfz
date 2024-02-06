#include <stdint.h>
#include <stdlib.h>

#include "numa.h"

extern "C" {
#include "numaif.h"
}

// Declare the missing functions in the numa.h header file.
struct bitmask *numa_get_run_node_mask_v2(void);
void numa_bitmask_free(struct bitmask *mask);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct bitmask *mask = NULL;
  mask = numa_get_run_node_mask_v2();
  if (mask != NULL) {
    numa_bitmask_free(mask);
  }
  return 0;
}