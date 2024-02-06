#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "iconveh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string src = stream.ConsumeRandomLengthString();
  std::string from_codeset = stream.ConsumeRandomLengthString();
  std::string to_codeset = stream.ConsumeRandomLengthString();
  int handler = stream.ConsumeIntegral<int>();

  char* result = str_iconveh(src.c_str(), from_codeset.c_str(), to_codeset.c_str(), handler);

  free(result);

  return 0;
}