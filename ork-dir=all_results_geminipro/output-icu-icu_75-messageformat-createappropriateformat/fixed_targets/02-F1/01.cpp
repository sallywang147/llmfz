#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/messageformat.h"
#include "unicode/parseerr.h"
#include "unicode/unistr.h"

extern "C" {
const char *GetRandomStyle(uint8_t rnd) {
  const char *styles[] = {"full", "long", "medium", "short"};
  return styles[rnd % 4];
}

const char *GetRandomFormattableType(uint8_t rnd) {
  const char *types[] = {"date", "time", "number", "currency"};
  return types[rnd % 4];
}
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
  // Byte 0 and 1 randomly select a Style
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  const char *style = GetRandomStyle(rnd);

  // Byte 2 and 3 randomly select a Formattable Type
  std::memcpy(&rnd, fuzzData.data(), sizeof(rnd));
  fuzzData.remove_prefix(sizeof(rnd));
  const char *type = GetRandomFormattableType(rnd);

  // Byte 4 randomly select a Formattable Type
  int formattableType = *fuzzData.data();
  fuzzData.remove_prefix(1);

  UErrorCode status = U_ZERO_ERROR;
  icu::UnicodeString uType(type, -1, US_INV);
  icu::UnicodeString uStyle(style, -1, US_INV);
  icu::MessageFormat::createAppropriateFormat(uType, uStyle, &formattableType, &status);
  if (U_FAILURE(status))
    return 0;

  return EXIT_SUCCESS;
}