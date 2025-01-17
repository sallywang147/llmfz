#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/utypes.h"
#include "unicode/msgfmt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a MessageFormat object
  UErrorCode status = U_ZERO_ERROR;
  icu_75::MessageFormat msgFormat("", "en_US", status);
  if (U_FAILURE(status)) {
    return 0;
  }

  // Consume data from the stream to create a UnicodeString
  std::string patternString = stream.ConsumeRemainingBytesAsString();
  icu_75::UnicodeString pattern(patternString.c_str(), patternString.length());

  // Create a UParseError object
  UParseError parseError;

  // Call the target function
  msgFormat.applyPattern(pattern, parseError, &status);

  return 0;
}