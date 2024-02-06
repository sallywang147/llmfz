#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>

extern "C" {
#include "_GLOBAL__sub_I_ftfuzzer.cc"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  _GLOBAL__sub_I_ftfuzzer(data, size);
  return 0;
}