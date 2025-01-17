#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/numfmt.h"
#include "unicode/rbnf.h"
#include "unicode/uversion.h"

extern "C" {
#include "unicode/ustring.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);

  UErrorCode status = U_ZERO_ERROR;
  std::unique_ptr<icu::RuleBasedNumberFormat> fmt(
      icu::RuleBasedNumberFormat::createInstance(icu::Locale("en_US"), status));
  if (U_FAILURE(status)) {
    return 0;
  }

  // Byte 0 and 1 randomly select a number
  size_t number;
  std::memcpy(&number, fuzzData.data(), sizeof(number));
  fuzzData.remove_prefix(sizeof(number));

  // Byte 2 and 3 randomly select a rule set
  icu::UnicodeString ruleSetName;
  std::memcpy(ruleSetName.getBuffer(2), fuzzData.data(), 2);
  ruleSetName.releaseBuffer(2);
  fuzzData.remove_prefix(2);

  // Byte 4 randomly select a FieldPosition
  icu::FieldPosition fieldPosition;
  std::memcpy(&fieldPosition, fuzzData.data(), sizeof(fieldPosition));
  fuzzData.remove_prefix(sizeof(fieldPosition));

  // Byte 5 randomly select a status
  int status_tmp;
  std::memcpy(&status_tmp, fuzzData.data(), sizeof(status_tmp));
  fuzzData.remove_prefix(sizeof(status_tmp));

  // Byte 6 randomly select a UnicodeString
  icu::UnicodeString toAppendTo;
  std::memcpy(toAppendTo.getBuffer(1), fuzzData.data(), 1);
  toAppendTo.releaseBuffer(1);
  fuzzData.remove_prefix(1);

  // Byte 7 randomly select a UnicodeString
  icu::UnicodeString result;
  std::memcpy(result.getBuffer(1), fuzzData.data(), 1);
  result.releaseBuffer(1);
  fuzzData.remove_prefix(1);

  fmt->format(number, ruleSetName, toAppendTo, fieldPosition, status);
  fmt->format(number, ruleSetName, result, fieldPosition, status);

  return EXIT_SUCCESS;
}