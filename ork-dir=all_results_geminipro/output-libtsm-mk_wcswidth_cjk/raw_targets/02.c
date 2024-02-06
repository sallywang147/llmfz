#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<int> pwcs(size);
  FuzzedDataProvider provider(data, size);
  for (size_t i = 0; i < size; i++) {
    pwcs[i] = provider.ConsumeIntegral<int>();
  }
  mk_wcswidth_cjk(pwcs.data(), size);
  return 0;
}