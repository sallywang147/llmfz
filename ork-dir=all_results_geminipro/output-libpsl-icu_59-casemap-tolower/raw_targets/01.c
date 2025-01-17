#include <stddef.h>
#include <stdint.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <unicode/casemap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const icu::CaseMap* case_map = icu::CaseMap::toLower();
  if (case_map == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::vector<short> src;
  std::vector<short> dest;
  while (provider.remaining_bytes() > 0) {
    src.push_back(provider.ConsumeIntegral<short>());
  }
  icu::Edits edits;
  int error_code = 0;
  case_map->toLower("", 0, src.data(), src.size(), dest.data(), dest.size(),
                    &edits, &error_code);
  return 0;
}