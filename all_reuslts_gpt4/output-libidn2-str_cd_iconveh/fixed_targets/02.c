#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "iconveh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  
  // Extract a string
  std::string src = stream.ConsumeRandomLengthString();
  
  // Extract integral values
  int handler = stream.ConsumeIntegral<int>();
  
  // Define and initialize iconveh_t struct
  struct iconveh_t cd;
  cd.cd = nullptr;
  cd.cd_invalid = nullptr;
  cd.invalid_count = 0;
  
  // Call the function
  char* result = str_cd_iconveh(const_cast<char*>(src.c_str()), &cd, handler);
  
  // Free the memory
  free(result);
  
  return 0;
}