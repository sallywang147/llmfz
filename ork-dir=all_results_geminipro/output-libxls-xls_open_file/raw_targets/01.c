#include "xls.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  int outError;
  xls_open_file((char *)Data, NULL, &outError);
  return 0;
}