#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract an integer to use as the method
  int method = stream.ConsumeIntegral<int>();

  // Call the function under test
  int result = get_quant_level(method);

  return 0;
}