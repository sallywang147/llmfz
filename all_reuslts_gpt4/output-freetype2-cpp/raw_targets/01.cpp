#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // This function does not take any parameters, so we don't need to use the data or size variables.
  // Call the function.
  _GLOBAL__sub_I_template.cpp();

  return 0;
}