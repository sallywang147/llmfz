#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/regex.h"
#include "unicode/unistr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> input_data = provider.ConsumeBytes<uint8_t>(input_size);
  icu::UnicodeString input_string((const char*)input_data.data(), input_size);

  size_t pattern_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> pattern_data = provider.ConsumeBytes<uint8_t>(pattern_size);
  icu::UnicodeString pattern_string((const char*)pattern_data.data(), pattern_size);

  UErrorCode status = U_ZERO_ERROR;
  icu::RegexMatcher matcher(pattern_string, status);
  if (U_FAILURE(status)) {
    return 0;
  }

  status = U_ZERO_ERROR;
  matcher.reset(input_string, status);
  if (U_FAILURE(status)) {
    return 0;
  }

  bool result = matcher.matches(status);
  if (U_FAILURE(status)) {
    return 0;
  }

  return static_cast<int>(result);
}