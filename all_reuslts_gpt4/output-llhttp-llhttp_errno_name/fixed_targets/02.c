#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "llhttp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume an integral value from the stream to use as the argument for llhttp_errno_name
  int err = stream.ConsumeIntegral<int>();
  
  // Call the function with the consumed argument
  char* name = llhttp_errno_name(err);
  
  return 0;
}