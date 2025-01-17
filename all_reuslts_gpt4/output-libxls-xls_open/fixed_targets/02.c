#include "xls.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string file = stream.ConsumeRandomLengthString();
  std::string charset = stream.ConsumeRemainingBytesAsString();

  struct xlsWorkBook* workbook = xls_open(const_cast<char*>(file.c_str()), const_cast<char*>(charset.c_str()));

  if (workbook) {
    xls_close_WB(workbook);
  }

  return 0;
}