// © 2023 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

// Fuzzer for ICU RuleBasedNumberFormat.

#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/numfmt.h"
#include "unicode/rulebasednumberformat.h"
#include "unicode/unistr.h" // Include the missing header file

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2 * sizeof(size_t) + 1)
    return 0;
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);
  // Byte 0 and 1 randomly select a number
  size_t number;
  std::memcpy(&number, fuzzData.data(), sizeof(number));
  fuzzData.remove_prefix(sizeof(number));

  // Byte 2 and 3 randomly select a RuleSet name
  icu::UnicodeString ruleSetName;
  ruleSetName.setTo(fuzzData.data(), static_cast<int32_t>(fuzzData.length()));
  fuzzData.remove_prefix(fuzzData.length());

  // Byte 4 randomly select a FieldPosition
  icu::FieldPosition fieldPosition;

  // Byte 5 and 6 randomly select a status
  int status;
  std::memcpy(&status, fuzzData.data(), sizeof(status));
  fuzzData.remove_prefix(sizeof(status));

  // Create a RuleBasedNumberFormat instance
  icu::RuleBasedNumberFormat fmt(ruleSetName, status);
  if (U_FAILURE(status))
    return 0;

  // Format the number
  icu::UnicodeString toAppendTo;
  fmt.format(number, toAppendTo, fieldPosition, status);

  return EXIT_SUCCESS;
}