#include <cstring>

#include "fuzzer_utils.h"

#include "unicode/messageformat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2)
    return 0;

  icu::StringPiece fuzzData(reinterpret_cast<const char *>(data), size);

  int status = 0;
  icu::MessageFormat fmt;
  fmt.cacheExplicitFormats(&status);
  if (U_FAILURE(status))
    return 0;

  return EXIT_SUCCESS;
}