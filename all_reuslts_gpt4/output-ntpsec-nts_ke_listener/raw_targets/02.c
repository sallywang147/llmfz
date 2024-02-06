#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ntpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string arg = stream.ConsumeRandomLengthString();
  char* result = nts_ke_listener(const_cast<char*>(arg.c_str()));

  // Free the result if necessary
  if (result) {
    free(result);
  }

  return 0;
}