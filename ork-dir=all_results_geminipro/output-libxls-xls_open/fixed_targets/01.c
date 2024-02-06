#include <string>
#include <sstream>
#include <iostream>

extern "C" {
#include "xls.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider Stream(Data, Size);
  std::string FileName = Stream.ConsumeRemainingBytesAsString();
  struct xlsWorkBook *WorkBook = xls_open(const_cast<char *>(FileName.c_str()), NULL);
  if (WorkBook) {
    xls_close_WB(WorkBook);
  }
  return 0;
}