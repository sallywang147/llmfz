#include "unicode/messageformat.h"
#include "unicode/parseerr.h"
#include "unicode/udata.h"
#include "fuzzer_utils.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);

  // Create a MessageFormat object.
  icu::MessageFormat fmt;

  // Parse the pattern.
  UParseError parseError;
  fmt.applyPattern(icu::UnicodeString(fuzzData, "utf-8"), &parseError);

  // Check for errors.
  if (parseError.errorCode != U_ZERO_ERROR) {
    return 0;
  }

  // Format a message.
  icu::UnicodeString message;
  fmt.format(icu::UnicodeString(), message, parseError);

  // Check for errors.
  if (parseError.errorCode != U_ZERO_ERROR) {
    return 0;
  }

  // Return success.
  return 0;
}