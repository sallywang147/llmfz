#include <stdio.h>
#include <stdlib.h>

#include "hal_thread.h"
#include "iec61850_server.h"

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  int out;
  MmsValue *value = NULL;
  value = MmsValue_decodeMmsData(data, 0, size, &out);

  if (value != NULL) {
    char *buffer = (char *)malloc(1024);
    char *result = MmsValue_printToBuffer(value, buffer, 1024);
    free(buffer);
    MmsValue_delete(value);
  }

  return 0;
}