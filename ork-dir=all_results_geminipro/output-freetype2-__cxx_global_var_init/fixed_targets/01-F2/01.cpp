#include <fuzzer/FuzzedDataProvider.h>
#include <stdlib.h>

extern "C" {
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  __cxx_global_var_init();
  return 0;
}
}