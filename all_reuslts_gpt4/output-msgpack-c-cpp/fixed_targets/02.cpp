#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Call the function
  _GLOBAL__sub_I_unpack_pack_fuzzer.cpp();

  return 0;
}