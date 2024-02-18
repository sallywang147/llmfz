#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" void _GLOBAL__sub_I_ftfuzzer_cc();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // The function does not take any parameters, so we don't need to use FuzzedDataProvider.
  _GLOBAL__sub_I_ftfuzzer_cc();
  return 0;
}