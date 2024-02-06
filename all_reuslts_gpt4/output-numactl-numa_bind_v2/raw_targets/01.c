#include "numa.h"
#include <stdint.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = str.c_str();

  struct bitmask *mask = numa_parse_nodestring(ptr);
  if (mask != NULL) {
    numa_bind_v2(mask);
    numa_bitmask_free(mask);
  }

  return 0;
}