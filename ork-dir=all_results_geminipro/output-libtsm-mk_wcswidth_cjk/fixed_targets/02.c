#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <wchar.h>  // Include the header file that defines mk_wcswidth_cjk

extern "C" {
#include <locale.h>  // Include the header file that defines setlocale
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<int> pwcs(size);
  FuzzedDataProvider provider(data, size);
  for (size_t i = 0; i < size; i++) {
    pwcs[i] = provider.ConsumeIntegral<int>();
  }
  setlocale(LC_ALL, "en_US.UTF-8");  // Set the locale to "en_US.UTF-8" to enable UTF-8 support
  mk_wcswidth_cjk(pwcs.data(), size);
  return 0;
}