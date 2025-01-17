// © 2023 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

// Fuzzer for ICU RuleBasedNumberFormat.

#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/rbnf.h"
#include "unicode/unistr.h"

icu::UnicodeString GetRandomRuleSetName(uint8_t rnd) {
  UErrorCode status = U_ZERO_ERROR;
  std::unique_ptr<icu::StringEnumeration> enumeration(icu::RuleBasedNumberFormat::getAvailableRuleSetNames(status));
  if (U_FAILURE(status))
    return icu::UnicodeString();
  int32_t count = enumeration->count(status);
  if (U_FAILURE(status))
    return icu::UnicodeString();
  int32_t i = rnd % count;
  const icu::UnicodeString *name = nullptr;
  do {
    name = enumeration->snext(status);
  } while (U_SUCCESS(status) && --i > 0);
  if (U_FAILURE(status))
    return icu::UnicodeString();
  return *name;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  uint16_t rnd;
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  if (size < 2 * sizeof(rnd) + 1)
    return 0;
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);
  // Byte 0 and 1 randomly select a RuleSet
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::UnicodeString ruleSetName = GetRandomRuleSetName(rnd);

  // Byte 2 and 3 randomly select a number
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  size_t number = rnd;

  // Byte 4 randomly select a Locale
  icu::Locale locale = GetRandomLocale(*fuzzData.data());
  fuzzData.remove_prefix(1);

  UErrorCode status = U_ZERO_ERROR;
  std::unique_ptr<icu::RuleBasedNumberFormat> fmt(icu::RuleBasedNumberFormat::createInstance(ruleSetName, locale, status));
  if (U_FAILURE(status))
    return 0;
  icu::UnicodeString toAppendTo;
  icu::FieldPosition fieldPosition;
  fmt->format(number, ruleSetName, &toAppendTo, &fieldPosition, &status);
  if (U_FAILURE(status))
    return 0;

  return EXIT_SUCCESS;
}