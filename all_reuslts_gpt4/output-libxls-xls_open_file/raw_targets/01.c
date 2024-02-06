#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "xls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRandomLengthString();
  std::string charset = stream.ConsumeRandomLengthString();

  int outError;
  struct xlsWorkBook *work_book = xls_open_file(const_cast<char*>(filename.c_str()), const_cast<char*>(charset.c_str()), &outError);
  if (work_book) {
    xls_close_WB(work_book);
  }

  return 0;
}