#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Since the function main_loop() doesn't take any arguments, we don't need to use the FuzzedDataProvider here.
  // Simply call the function.
  main_loop();
  
  return 0;
}