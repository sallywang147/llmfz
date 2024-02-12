#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include <cstdlib>
#include <stdint.h>

extern "C" {
#include <fuzzer/libfuzzer_macro.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  return 0;
}