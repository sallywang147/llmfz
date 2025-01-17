#include <stdio.h>
#include <stdlib.h>

#include "hal_thread.h"
#include "iec61850_server.h"

extern "C" {
#include "mms_value.h"
}

#include "mms_array.h"

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  int out;
  MmsValue *value = NULL;
  value = MmsValue_decodeMmsData(data, 0, size, &out);

  if (value != NULL) {
    int bufPos = 0;
    char buffer[1024];
    encodeArrayAccessResult(value, buffer, bufPos, true);
    MmsValue_delete(value);
  }

  return 0;
}