#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "unicode/messageformat.h"
#include "unicode/parseerr.h"
#include "unicode/unistr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  UErrorCode status = U_ZERO_ERROR;
  icu_75::MessageFormat msgFormat("", "en_US", status);
  if (U_FAILURE(status)) {
    return 0;
  }

  UParseError parseError;
  std::string pattern = stream.ConsumeRandomLengthString();
  icu_75::UnicodeString unicodePattern(pattern.c_str());

  msgFormat.applyPattern(unicodePattern, parseError, &status);

  return 0;
}