#include <fuzzer/FuzzedDataProvider.h>

#include <unicode/regex.h>
#include <unicode/unistr.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  UErrorCode status = U_ZERO_ERROR;
  icu::RegexMatcher m(icu::UnicodeString::fromUTF8(fdp.ConsumeRandomLengthString()),
                      0, status);
  if (U_FAILURE(status)) {
    return 0;
  }

  m.reset(icu::UnicodeString::fromUTF8(fdp.ConsumeRandomLengthString()));
  m.matches(status);

  return 0;
}