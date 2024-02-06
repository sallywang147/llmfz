#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" void mworker_loop();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As mworker_loop() doesn't take any arguments, we don't need FuzzedDataProvider in this case.
  // We just call the function.
  mworker_loop();
  return 0;
}