#include <iostream>
#include <string>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <unicode/rbnf.h>
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  std::string pattern = fuzzed_data.ConsumeRandomLengthString(size);
  std::string locale = fuzzed_data.ConsumeRandomLengthString(size);
  std::string number = fuzzed_data.ConsumeRandomLengthString(size);
  icu::UnicodeString pattern_icu(pattern.c_str(), pattern.size());
  icu::UnicodeString locale_icu(locale.c_str(), locale.size());
  icu::UnicodeString number_icu(number.c_str(), number.size());
  icu::Locale loc(locale_icu.getBuffer());
  icu::UErrorCode status = U_ZERO_ERROR;
  icu::RuleBasedNumberFormat* formatter =
      icu::RuleBasedNumberFormat::createInstance(pattern_icu, loc, status);
  if (U_FAILURE(status)) {
    return 0;
  }
  icu::UnicodeString formatted;
  formatter->format(number_icu, formatted, status);
  if (U_FAILURE(status)) {
    return 0;
  }
  return 0;
}