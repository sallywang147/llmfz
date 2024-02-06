#include <stdio.h>
#include <stdlib.h>

#include "hal_thread.h"
#include "iec61850_server.h"

extern "C" {
#include "mms_variable_specification.h"
#include "mms_value.h"
}

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  struct sMmsVariableSpecification *typeSpec = NULL;
  MmsValue *value = NULL;

  typeSpec = MmsVariableSpecification_new();
  if (typeSpec == NULL) {
    return 0;
  }

  value = MmsValue_newDefaultValue(typeSpec);

  if (value != NULL) {
    MmsValue_delete(value);
  }

  MmsVariableSpecification_delete(typeSpec);

  return 0;
}