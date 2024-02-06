#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" void ixheaacd_hbe_apply_ifft_336(float * , float * , int , int );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  const size_t max_size = 336;
  std::vector<float> input1 = provider.ConsumeBytes<float>(provider.ConsumeIntegralInRange<size_t>(0, max_size));
  std::vector<float> input2 = provider.ConsumeBytes<float>(provider.ConsumeIntegralInRange<size_t>(0, max_size));
  int input3 = provider.ConsumeIntegral<int>();
  int input4 = provider.ConsumeIntegral<int>();

  if (input1.empty() || input2.empty()) {
    return 0;
  }

  ixheaacd_hbe_apply_ifft_336(input1.data(), input2.data(), input3, input4);

  return 0;
}