#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int mk_wcswidth_cjk(int * pwcs, size_t n);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t array_size = stream.remaining_bytes() / sizeof(int);
  std::vector<int> pwcs(array_size);
  for (size_t i = 0; i < array_size; ++i) {
    pwcs[i] = stream.ConsumeIntegral<int>();
  }

  mk_wcswidth_cjk(pwcs.data(), array_size);

  return 0;
}