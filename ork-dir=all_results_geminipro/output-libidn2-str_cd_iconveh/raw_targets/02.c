#include <fuzzer/FuzzedDataProvider.h>

#include <string>

extern "C" {
#include "iconv.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string src = stream.ConsumeRemainingBytesAsString();
  const std::string cd = stream.ConsumeRemainingBytesAsString();
  const int handler = stream.ConsumeIntegral<int>();

  char* result = str_cd_iconveh(const_cast<char*>(src.c_str()),
                                const_cast<char*>(cd.c_str()), handler);
  free(result);
  return 0;
}