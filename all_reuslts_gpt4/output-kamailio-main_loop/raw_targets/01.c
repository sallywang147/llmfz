#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" int main_loop();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function main_loop() doesn't take any parameters, we don't need to use FuzzedDataProvider.
  // Just call the function.
  main_loop();
  return 0;
}