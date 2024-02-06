#include "numa.h"
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct bitmask *mask = NULL;

  mask = numa_get_run_node_mask_v2();
  if (mask != NULL) {
    numa_bitmask_free(mask);
  }

  return 0;
}