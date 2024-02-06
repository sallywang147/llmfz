#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const int method = provider.ConsumeIntegral<int>();
  get_quant_level(method);
  return 0;
}