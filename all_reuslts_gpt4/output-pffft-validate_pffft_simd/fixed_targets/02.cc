#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // The function doesn't take any arguments, so we don't need to generate any inputs.
  // We just call the function.
  validate_pffft_simd();

  return 0;
}