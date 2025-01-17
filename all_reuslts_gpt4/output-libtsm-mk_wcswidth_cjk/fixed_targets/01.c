#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int mk_wcswidth_cjk(int * pwcs, size_t n);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t array_size = stream.ConsumeIntegralInRange<size_t>(0, 256);
  std::vector<int> pwcs(array_size);

  for (size_t i = 0; i < array_size; ++i) {
    pwcs[i] = stream.ConsumeIntegral<int>();
  }

  mk_wcswidth_cjk(pwcs.data(), pwcs.size());

  return 0;
}