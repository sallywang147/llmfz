#include <fuzzer/FuzzedDataProvider.h>
#include "xls.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string file = stream.ConsumeRandomLengthString();
  std::string charset = stream.ConsumeRemainingBytesAsString();

  struct xlsWorkBook* work_book = xls_open(const_cast<char*>(file.c_str()), const_cast<char*>(charset.c_str()));

  if (work_book) {
    xls_close_WB(work_book);
  }

  return 0;
}