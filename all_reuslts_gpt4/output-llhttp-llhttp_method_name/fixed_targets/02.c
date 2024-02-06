#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "llhttp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract integral value
  int method = stream.ConsumeIntegral<int>();
  
  // Call the function with the extracted value
  char* method_name = llhttp_method_name(method);

  return 0;
}