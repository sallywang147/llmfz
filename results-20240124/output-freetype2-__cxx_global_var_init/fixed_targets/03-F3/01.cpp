#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>

extern "C" {
#include <cstdint>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume all bytes
  stream.ConsumeRemainingBytes();

  // Call __cxx_global_var_init() to initialize global variables
  __cxx_global_var_init();

  return 0;
}