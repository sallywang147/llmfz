#include <stddef.h>
#include <stdint.h>

#include "TPMS_CAPABILITY_DATA_fp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct TPMS_CAPABILITY_DATA target;
  int size_copy = size;
  char *buffer = (char *)data;
  TPMS_CAPABILITY_DATA_Unmarshal(&target, &buffer, &size_copy);
  return 0;
}