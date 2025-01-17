#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" void ixheaacd_hbe_apply_ifft_224(float * , float * , int , int );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t size1 = stream.remaining_bytes() / 2;
  const size_t size2 = stream.remaining_bytes() - size1;

  std::vector<float> floatArray1 = stream.ConsumeBytes<float>(size1);
  std::vector<float> floatArray2 = stream.ConsumeBytes<float>(size2);

  int int1 = stream.ConsumeIntegral<int>();
  int int2 = stream.ConsumeIntegral<int>();

  ixheaacd_hbe_apply_ifft_224(floatArray1.data(), floatArray2.data(), int1, int2);

  return 0;
}