#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>

extern "C" {
#include "get_quant_level.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  int method = fdp.ConsumeIntegral<int>();
  get_quant_level(method);
  return 0;
}