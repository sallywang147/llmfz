 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  for (size_t i = 0; i < size; i++) {
    provider.ConsumeBool();
  }
  __cxx_global_var_init();
  return 0;
}