#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/rbnf.h"
#include "unicode/unistr.h"

extern "C" {
#include "unicode/locid.h"
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
  // Byte 0 and 1 randomly select a RuleBasedNumberFormat
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::RuleBasedNumberFormat *formatter = CreateRandomRuleBasedNumberFormat(rnd);

  // Byte 1 and 2 randomly select a Locale
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::Locale locale = GetRandomLocale(rnd);

  // Byte 4 randomly select a number
  uint64_t number;
  std::memcpy(&number, fuzzData.data(), sizeof(number));
  fuzzData.remove_prefix(sizeof(number));

  // Byte 5 randomly select a rule set name
  icu::UnicodeString ruleSetName;
  uint8_t ruleSetNameLength = *fuzzData.data();
  fuzzData.remove_prefix(1);
  if (ruleSetNameLength > 0) {
    if (ruleSetNameLength > fuzzData.length()) {
      ruleSetNameLength = fuzzData.length();
    }
    ruleSetName.append(fuzzData.data(), ruleSetNameLength);
    fuzzData.remove_prefix(ruleSetNameLength);
  }

  // Byte 6 randomly select a string to append to
  icu::UnicodeString toAppendTo;
  uint8_t toAppendToLength = *fuzzData.data();
  fuzzData.remove_prefix(1);
  if (toAppendToLength > 0) {
    if (toAppendToLength > fuzzData.length()) {
      toAppendToLength = fuzzData.length();
    }
    toAppendTo.append(fuzzData.data(), toAppendToLength);
    fuzzData.remove_prefix(toAppendToLength);
  }

  icu::FieldPosition fieldPosition;
  int32_t status = 0;
  icu::UnicodeString result;
  formatter->format(number, ruleSetName, toAppendTo, fieldPosition, &result, &status);
  return EXIT_SUCCESS;
}