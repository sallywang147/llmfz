#include <fuzzer/FuzzedDataProvider.h>
#include <pffft.h>

extern "C" {
#include "pffft.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Skip the first 4 bytes, which are the size of the input.
  stream.ConsumeIntegral<uint32_t>();

  // Extract an array of bytes as a vector.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 10000));

  // Validate PFFFT SIMD.
  validate_pffft_simd(bytes.data(), bytes.size());

  return 0;
}

// Define the function validate_pffft_simd.
void validate_pffft_simd(const uint8_t *data, size_t size) {
  // Perform the validation logic here.
  pffft_simd_state state;
  pffft_simd_init(&state);
  pffft_simd_update(&state, data, size);
  pffft_simd_final(&state);
}