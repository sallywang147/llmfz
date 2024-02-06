#include "xls.h"

extern "C" {
#include <stdlib.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  xlsWorkBook *work_book = xls_open_buffer(Data, Size, NULL, NULL);
  if (work_book) {
    char *css = xls_getCSS(work_book);
    free(css);
    xls_close_WB(work_book);
  }
  return 0;
}