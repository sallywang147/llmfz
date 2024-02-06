#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <unicode/uloc.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }
  FuzzedDataProvider provider(data, size);
  const size_t localeIDCapacity = provider.ConsumeIntegralInRange<size_t>(1, 256);
  std::vector<char> localeID(localeIDCapacity, '\0');
  provider.ConsumeBytes(localeID.data(), localeIDCapacity - 1);
  const size_t langtagCapacity = provider.ConsumeIntegralInRange<size_t>(1, 256);
  std::vector<char> langtag(langtagCapacity, '\0');
  int status = 0;
  char strict = provider.ConsumeBool() ? 't' : 'f';
  uloc_toLanguageTag_59(localeID.data(), langtag.data(), langtagCapacity, strict, &status);
  return 0;
}