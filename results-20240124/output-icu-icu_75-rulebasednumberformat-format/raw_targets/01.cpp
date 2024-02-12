 // © 2023 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

// Fuzzer for ICU RuleBasedNumberFormat.

#include "unicode/rbnf.h"
#include "unicode/unistr.h"
#include "fuzzer_utils.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);

  // Byte 0 and 1 randomly select a number
  uint16_t rnd;
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  size_t number = rnd;

  // Byte 2 and 3 randomly select a rule set name
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::UnicodeString ruleSetName = GetRandomUnicodeString(rnd);

  // Byte 4 randomly select an append to string
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::UnicodeString toAppendTo = GetRandomUnicodeString(rnd);

  // Byte 5 randomly select a FieldPosition
  uint8_t fieldPosition = *fuzzData.data();
  fuzzData.remove_prefix(1);

  // Byte 6 and 7 randomly select a status
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  int status = rnd;

  UErrorCode status_ = U_ZERO_ERROR;
  std::unique_ptr<icu::RuleBasedNumberFormat> rbnf(
      icu::RuleBasedNumberFormat::createInstance(ruleSetName, status_));
  if (U_FAILURE(status_))
    return 0;
  icu::UnicodeString result;
  rbnf->format(number, result, toAppendTo, nullptr, &status_);
  return EXIT_SUCCESS;
}