#include <fuzzer/FuzzedDataProvider.h>
#include "astc_physical_to_symbolic.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int method = stream.ConsumeIntegral<int>();
  int quant_level = get_quant_level(method);
  return 0;
}