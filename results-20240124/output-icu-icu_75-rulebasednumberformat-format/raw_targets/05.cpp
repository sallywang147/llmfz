 // © 2023 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

// Fuzzer for ICU RuleBasedNumberFormat.

#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/rbnf.h"
#include "unicode/ustring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  if (size < sizeof(size_t) + 1)
    return 0;
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);
  // Byte 0 and 1 randomly select a UnicodeString
  size_t rnd;
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::UnicodeString ruleSetName = GetRandomUnicodeString(rnd);

  // Byte 2 and 3 randomly select a UnicodeString
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::UnicodeString toAppendTo = GetRandomUnicodeString(rnd);

  // Byte 4 and 5 randomly select a number
  size_t number;
  std::memcpy(&number, fuzzData.data(), sizeof(number));
  fuzzData.remove_prefix(sizeof(number));

  UErrorCode status = U_ZERO_ERROR;
  icu::RuleBasedNumberFormat fmt(ruleSetName, status);
  if (U_FAILURE(status))
    return 0;
  fmt.format(number, toAppendTo, status);
  if (U_FAILURE(status))
    return 0;
  return EXIT_SUCCESS;
}