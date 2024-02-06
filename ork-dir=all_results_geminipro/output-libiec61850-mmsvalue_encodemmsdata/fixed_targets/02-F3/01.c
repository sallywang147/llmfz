#include <stdio.h>
#include <stdlib.h>

#include "hal_thread.h"
#include "iec61850_server.h"

extern "C" {
#include "mms_value.h"
}

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  int out;
  MmsValue *value = NULL;
  value = MmsValue_decodeMmsData(data, 0, size, &out);

  if (value != NULL) {
    char *buffer = new char[1024];
    MmsValue_encodeMmsData(value, buffer, 0, true);
    delete[] buffer;

    MmsValue_delete(value);
  }

  return 0;
}
```

Changes made:

* The `#include` directive for `mms_value.h` was wrapped with `extern "C" {}`.
* The `MmsValue_delete` function was declared in the `mms_value.h` header file.