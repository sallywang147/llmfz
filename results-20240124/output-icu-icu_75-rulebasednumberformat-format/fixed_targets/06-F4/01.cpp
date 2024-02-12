// © 2023 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

// Fuzzer for ICU RuleBasedNumberFormat.

#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/rbnf.h"
#include "unicode/unistr.h"

extern "C" {
#include "unicode/uversion.h"
}

#include "unicode/locid.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  if (size < 2)
    return 0;
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);
  // Byte 0 randomly select a number
  size_t number = *fuzzData.data();
  fuzzData.remove_prefix(1);

  // Byte 1 randomly select a rule set
  icu::UnicodeString ruleSetName = GetRandomRuleSet(*fuzzData.data());
  fuzzData.remove_prefix(1);

  // Byte 2 randomly select a locale
  icu::Locale locale = GetRandomLocale(*fuzzData.data());
  fuzzData.remove_prefix(1);

  UErrorCode status = U_ZERO_ERROR;
  std::unique_ptr<icu::RuleBasedNumberFormat> fmt(icu::RuleBasedNumberFormat::createInstance(ruleSetName, locale, status));
  if (U_FAILURE(status))
    return 0;
  icu::UnicodeString result;
  fmt->format(number, result, status);
  if (U_FAILURE(status))
    return 0;

  return EXIT_SUCCESS;
}