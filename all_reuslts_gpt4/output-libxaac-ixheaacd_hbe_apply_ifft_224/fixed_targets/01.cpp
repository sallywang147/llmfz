#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" void ixheaacd_hbe_apply_ifft_224(float *, float *, int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // The function takes two float pointers, two integers as parameters.
  // We'll need to ensure that we have enough data for at least two floats and two integers.
  if (stream.remaining_bytes() < (2 * sizeof(float) + 2 * sizeof(int))) {
    return 0;
  }

  // Extract floats and integers from the data.
  float float1 = stream.ConsumeFloatingPoint<float>();
  float float2 = stream.ConsumeFloatingPoint<float>();
  int int1 = stream.ConsumeIntegral<int>();
  int int2 = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  ixheaacd_hbe_apply_ifft_224(&float1, &float2, int1, int2);

  return 0;
}