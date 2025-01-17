#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <wchar.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t n = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<int> pwcs(n);
  for (size_t i = 0; i < n; i++) {
    pwcs[i] = provider.ConsumeIntegral<int>();
  }
  mk_wcswidth_cjk(pwcs.data(), n);
  return 0;
}