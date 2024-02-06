#include <fuzzer/FuzzedDataProvider.h>
#include <stdlib.h>

extern "C" {
#include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  // Call the global variable initialization function.
  __cxx_global_var_init();
  return 0;
}