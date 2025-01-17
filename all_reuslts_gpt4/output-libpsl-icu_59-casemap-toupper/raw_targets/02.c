#include <stdint.h>
#include <string.h>
#include <unicode/casemap.h>
#include <unicode/edits.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  const int kMaxSize = 256;
  const int srcLength = stream.ConsumeIntegralInRange<int>(1, kMaxSize);
  const int destCapacity = stream.ConsumeIntegralInRange<int>(1, kMaxSize);
  const int options = stream.ConsumeIntegral<int>();
  int errorCode = 0;

  // Consume the data for the locale and src arrays.
  std::string locale = stream.ConsumeBytesAsString(srcLength);
  std::vector<short> src = stream.ConsumeBytes<short>(srcLength);
  std::vector<short> dest(destCapacity);

  // Create an Edits object to pass to the function.
  icu_59::Edits edits;

  // Call the function under test.
  icu_59::CaseMap::toUpper(locale.c_str(), options, src.data(), srcLength, dest.data(), destCapacity, &edits, &errorCode);

  return 0;
}