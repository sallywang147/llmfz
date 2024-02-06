#include <cstdio>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  auto str1 = provider.ConsumeBytes<char>(len);
  len = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  auto str2 = provider.ConsumeBytes<char>(len);

  printf("%s %s\n", str1.data(), str2.data());
  return 0;
}