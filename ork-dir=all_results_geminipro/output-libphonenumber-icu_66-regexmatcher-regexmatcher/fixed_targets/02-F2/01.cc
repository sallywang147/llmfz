#include <unicode/utypes.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "unicode/regex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  icu::RegexMatcher::UText regexp;
  regexp.flags = UREGEX_CASE_INSENSITIVE;
  regexp.length = fuzzed_data.ConsumeIntegralInRange<int>(0, 1024);
  regexp.nativeChars = static_cast<UChar *>(
      malloc(sizeof(UChar) * (regexp.length + 1)));
  fuzzed_data.ConsumeBytes<UChar>(regexp.nativeChars, regexp.length);
  regexp.nativeChars[regexp.length] = 0;

  int status = 0;
  icu::RegexMatcher matcher(regexp, status);

  free(regexp.nativeChars);

  return 0;
}