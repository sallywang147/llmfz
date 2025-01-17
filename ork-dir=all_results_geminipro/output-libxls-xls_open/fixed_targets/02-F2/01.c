#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" {
#include "xls.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string file = stream.ConsumeRemainingBytesAsString();
  std::string charset = stream.ConsumeRemainingBytesAsString();

  xls_open(const_cast<char*>(file.c_str()), const_cast<char*>(charset.c_str()));
  return 0;
}