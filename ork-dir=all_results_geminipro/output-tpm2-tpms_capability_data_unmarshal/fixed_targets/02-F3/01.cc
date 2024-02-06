#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include "TPMS_CAPABILITY_DATA_fp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct TPMS_CAPABILITY_DATA target;
  char *buffer = (char *)data;
  int size_left = size;

  int ret = TPMS_CAPABILITY_DATA_Unmarshal(&target, &buffer, &size_left);
  if (ret != 0) {
    return 0;
  }

  memset(&target, 0, sizeof(target));
  ret = TPMS_CAPABILITY_DATA_Unmarshal(&target, &buffer, &size_left);
  if (ret != 0) {
    return 0;
  }

  return 0;
}
```

The original code had no issues.