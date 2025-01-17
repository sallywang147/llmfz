#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <unicode/ustring.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t kMaxStringLength = 100;
  std::vector<short> src(kMaxStringLength);
  std::vector<short> dest(kMaxStringLength);
  for (size_t i = 0; i < kMaxStringLength; i++) {
    src[i] = provider.ConsumeIntegral<short>();
  }
  const size_t srcLength = provider.ConsumeIntegralInRange<size_t>(0, kMaxStringLength);
  const size_t destCapacity = provider.ConsumeIntegralInRange<size_t>(0, kMaxStringLength);
  std::vector<char> locale(kMaxStringLength);
  for (size_t i = 0; i < kMaxStringLength; i++) {
    locale[i] = provider.ConsumeIntegral<char>();
  }
  const size_t localeLength = provider.ConsumeIntegralInRange<size_t>(0, kMaxStringLength);
  int pErrorCode;
  u_strToUpper_59(dest.data(), destCapacity, src.data(), srcLength, locale.data(), &pErrorCode);
  return 0;
}