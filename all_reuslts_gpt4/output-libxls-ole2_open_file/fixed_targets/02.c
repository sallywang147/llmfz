#include <fuzzer/FuzzedDataProvider.h>

#include "ole2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string file = stream.ConsumeRandomLengthString();
  struct OLE2* ole2File = ole2_open_file(const_cast<char*>(file.c_str()));

  if (ole2File) {
    ole2_close(ole2File);
  }

  return 0;
}