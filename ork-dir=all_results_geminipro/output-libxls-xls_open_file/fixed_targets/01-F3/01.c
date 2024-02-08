#include "xls.h"

extern "C" {
#include <stdint.h>
}

XLS_ERROR LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  XLS_ERROR outError;
  xls_open_file((char *)Data, NULL, &outError);
  return outError;
}