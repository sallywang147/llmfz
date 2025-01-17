#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate inputs.
  const size_t localeID_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string localeID(localeID_size, '\0');
  provider.ConsumeBytes(&localeID[0], localeID_size);

  const size_t appendAt_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string appendAt(appendAt_size, '\0');
  provider.ConsumeBytes(&appendAt[0], appendAt_size);

  const int capacity = provider.ConsumeIntegralInRange<int>(-100, 100);
  const char strict = provider.ConsumeBool();
  const char hadPosix = provider.ConsumeBool();

  int status = -1;
  // Call the function.
  const int ret = _appendKeywordsToLanguageTag(localeID.data(), appendAt.data(), capacity, strict, hadPosix, &status);
  if (ret < 0) {
    // The function failed.
    return 0;
  }

  // Consume the remaining bytes.
  provider.ConsumeRemainingBytes();

  return 0;
}