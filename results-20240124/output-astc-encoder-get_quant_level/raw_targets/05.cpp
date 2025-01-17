 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int method = stream.ConsumeIntegralInRange<int>(0, 255);
  get_quant_level(method);
  return 0;
}