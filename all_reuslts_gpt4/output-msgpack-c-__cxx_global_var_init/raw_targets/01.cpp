#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Since __cxx_global_var_init() doesn't take any parameters, we don't need to use the data or size parameters.
  // Just call the function.
  __cxx_global_var_init();

  return 0;
}