#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" {
#include "astc_physical_to_symbolic.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int method = stream.ConsumeIntegral<int>();
  get_quant_level(method);
  return 0;
}