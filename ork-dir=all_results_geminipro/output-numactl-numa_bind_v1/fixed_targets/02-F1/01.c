#include "numa.h"
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <string.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct nodemask_t *mask = NULL;

  char *fuzz_str1 = malloc(size + 1);
  memcpy(fuzz_str1, data, size);
  fuzz_str1[size] = '\0';

  mask = numa_parse_nodestring(fuzz_str1);
  if (mask != NULL) {
    numa_bind_v1(mask);
    numa_bitmask_free(mask);
  }

  free(fuzz_str1);
  return 0;
}