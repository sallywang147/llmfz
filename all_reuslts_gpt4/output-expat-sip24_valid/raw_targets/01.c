#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // For a function with no parameters, we don't need to use the input data.
  // Simply call the function.
  sip24_valid();

  return 0;
}