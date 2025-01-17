#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
  void mworker_loop();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function mworker_loop() does not take any parameters, we don't need to use the data and size parameters.
  // We just call the function.
  mworker_loop();
  return 0;
}