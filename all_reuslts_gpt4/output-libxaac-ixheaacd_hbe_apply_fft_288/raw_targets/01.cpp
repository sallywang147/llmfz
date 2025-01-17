#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" void ixheaacd_hbe_apply_fft_288(float * , float * , int , int );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(int) * 2) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  // Allocate space for two float arrays with the remaining size / 2 / sizeof(float).
  size_t float_array_size = fuzzed_data.remaining_bytes() / 2 / sizeof(float);
  std::vector<float> float_array1(float_array_size);
  std::vector<float> float_array2(float_array_size);

  // Fill the float arrays with data.
  for (size_t i = 0; i < float_array_size; ++i) {
    float_array1[i] = fuzzed_data.ConsumeFloatingPoint<float>();
    float_array2[i] = fuzzed_data.ConsumeFloatingPoint<float>();
  }

  int int1 = fuzzed_data.ConsumeIntegral<int>();
  int int2 = fuzzed_data.ConsumeIntegral<int>();

  ixheaacd_hbe_apply_fft_288(float_array1.data(), float_array2.data(), int1, int2);

  return 0;
}