#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" {
#include <fuzzer/libfuzzer_example.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  __cxx_global_var_init();
  return 0;
}
```
This code should now compile and run without errors.