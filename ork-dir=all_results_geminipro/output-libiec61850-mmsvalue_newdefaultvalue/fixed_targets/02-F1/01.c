#include <stdio.h>
#include <stdlib.h>

#include "hal_thread.h"
#include "iec61850_server.h"

extern "C" {
#include "mms_value.h"
}

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  MmsVariableSpecification *typeSpec = NULL;
  MmsValue *value = NULL;

  value = MmsValue_newDefaultValue(typeSpec);

  if (value != NULL) {
    MmsValue_delete(value);
  }

  return 0;
}