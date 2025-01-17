#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" void ixheaacd_hbe_apply_fft_288(float * , float * , int , int );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(int)*2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int arg3 = stream.ConsumeIntegral<int>();
  int arg4 = stream.ConsumeIntegral<int>();

  std::vector<float> arg1 = stream.ConsumeRemainingBytes<float>();
  std::vector<float> arg2(arg1.size());

  if (arg1.size() > 0) {
    ixheaacd_hbe_apply_fft_288(arg1.data(), arg2.data(), arg3, arg4);
  }

  return 0;
}