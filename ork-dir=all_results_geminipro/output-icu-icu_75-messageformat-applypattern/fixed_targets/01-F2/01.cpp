#include <cstring>
#include <string>

#include "fuzzer_utils.h"

extern "C" {
#include "unicode/messageformat.h"
#include "unicode/parseerr.h"
#include "unicode/unistr.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  UErrorCode status = U_ZERO_ERROR;
  icu::MessageFormat fmt;
  icu::UnicodeString pattern;

  // Set the limit for the test data to 1000 bytes to avoid timeout for a
  // very long list of operations.
  if (size > 1000) {
    size = 1000;
  }
  if (size < 1)
    return 0;
  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);

  // Byte 0 randomly select a Locale
  int32_t rnd;
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  icu::Locale locale = GetRandomLocale(rnd);

  // Byte 1 randomly select a pattern
  size_t len = fuzzData.length();
  if (len > 0) {
    pattern.setTo(FALSE, fuzzData.data(), len);
    fuzzData.remove_prefix(len);
  }

  // Byte 2 randomly select a ParseError
  UParseError parseError;
  std::memcpy(&parseError, fuzzData.data(), sizeof(parseError));
  fuzzData.remove_prefix(sizeof(parseError));

  fmt.applyPattern(pattern, parseError, status);
  if (U_FAILURE(status))
    return 0;
  icu::UnicodeString result;
  fmt.format(result, status);
  if (U_FAILURE(status))
    return 0;

  return EXIT_SUCCESS;
}