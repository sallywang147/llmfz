#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // This function doesn't take any arguments, so we don't need to use the FuzzedDataProvider.
  // Just call the function.
  __cxx_global_var_init();

  return 0;
}