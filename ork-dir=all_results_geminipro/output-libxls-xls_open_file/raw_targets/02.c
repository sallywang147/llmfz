#include "xls.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  int outError;
  struct xlsWorkBook *work_book = xls_open_file((char *)Data, NULL, &outError);
  if (work_book) {
    xls_close_WB(work_book);
  }
  return 0;
}