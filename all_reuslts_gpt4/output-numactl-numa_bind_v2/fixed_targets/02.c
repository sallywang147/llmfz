#include "numa.h"
#include <stdint.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  struct bitmask *mask = numa_parse_nodestring(str.c_str());

  if (mask != NULL) {
    numa_bind_v2(mask);
    numa_bitmask_free(mask);
  }

  return 0;
}