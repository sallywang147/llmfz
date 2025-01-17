#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/messageformat.h"
#include "unicode/unistr.h"
#include "unicode/parseerr.h"

extern "C" {
#include "unicode/format.h"
}

const char *GetRandomFormattableType(uint8_t rnd) {
  const char *types[] = {"date", "time", "number", "spellout"};
  return types[rnd % 4];
}

const char *GetRandomStyle(uint8_t rnd) {
  const char *styles[] = {"full", "long", "medium", "short"};
  return styles[rnd % 4];
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
  // Byte 0 and 1 randomly select a formattable type
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  const char *type = GetRandomFormattableType(rnd);

  // Byte 1 and 2 randomly select a style
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  const char *style = GetRandomStyle(rnd);

  // Byte 4 randomly select a formattable type
  const char *formattableType = GetRandomFormattableType(*fuzzData.data());
  fuzzData.remove_prefix(1);

  UErrorCode status = U_ZERO_ERROR;
  icu::UnicodeString uType(type, -1, US_INV);
  icu::UnicodeString uStyle(style, -1, US_INV);
  icu::UnicodeString uFormattableType(formattableType, -1, US_INV);
  icu::MessageFormat fmt;
  icu::Format *format = fmt.createAppropriateFormat(uType, uStyle, &uFormattableType, &status);
  if (U_FAILURE(status))
    return 0;
  if (format == nullptr)
    return 0;
  delete format;

  return EXIT_SUCCESS;
}