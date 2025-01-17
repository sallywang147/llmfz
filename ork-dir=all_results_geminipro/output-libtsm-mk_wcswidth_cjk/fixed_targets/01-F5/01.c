#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include <locale.h>
#include <uchar.h>

extern "C" {
#include <uchar.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t n = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<int> pwcs(n);
  for (size_t i = 0; i < n; i++) {
    pwcs[i] = provider.ConsumeIntegral<int>();
  }
  setlocale(LC_ALL, "en_US.UTF-8");
  mk_wcswidth_cjk(pwcs.data(), n);
  return 0;
}