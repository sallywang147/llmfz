#include <cstdint>
#include <cstring>
#include <vector>
#include <unicode/casemap.h>
#include <unicode/edits.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);

  std::string locale = stream.ConsumeRandomLengthString();
  int options = stream.ConsumeIntegral<int>();
  int srcLength = stream.ConsumeIntegralInRange<int>(0, 100);
  std::vector<short> src = stream.ConsumeIntegralVector<short>(srcLength);
  int destCapacity = stream.ConsumeIntegralInRange<int>(0, 100);
  std::vector<short> dest(destCapacity);
  icu_59::Edits edits;
  int errorCode = 0;

  icu_59::CaseMap::toLower(locale.c_str(), options, src.data(), srcLength, dest.data(), destCapacity, &edits, &errorCode);

  return 0;
}