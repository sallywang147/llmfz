#include "numa.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Call the function
  numa_get_run_node_mask_v1();

  return 0;
}