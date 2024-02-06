#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  // Consume all bytes.
  stream.ConsumeRemainingBytes();
  // Call the function.
  __cxx_global_var_init();
  return 0;
}