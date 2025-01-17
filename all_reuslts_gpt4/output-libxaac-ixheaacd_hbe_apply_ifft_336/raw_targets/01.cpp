#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" void ixheaacd_hbe_apply_ifft_336(float *, float *, int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t num_floats = 336;
  std::vector<float> input1(num_floats);
  std::vector<float> input2(num_floats);

  for (size_t i = 0; i < num_floats; ++i) {
    input1[i] = stream.ConsumeFloatingPoint<float>();
    input2[i] = stream.ConsumeFloatingPoint<float>();
  }

  int arg1 = stream.ConsumeIntegral<int>();
  int arg2 = stream.ConsumeIntegral<int>();

  ixheaacd_hbe_apply_ifft_336(input1.data(), input2.data(), arg1, arg2);

  return 0;
}