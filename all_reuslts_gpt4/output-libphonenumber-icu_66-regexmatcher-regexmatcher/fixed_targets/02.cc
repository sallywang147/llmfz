#include <fuzzer/FuzzedDataProvider.h>
#include <unicode/regex.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  UErrorCode status = U_ZERO_ERROR;
  icu_66::RegexMatcher matcher(nullptr, 0, &status);
  if (U_FAILURE(status)) {
    return 0;
  }

  UText* utext = utext_openUTF8(nullptr, reinterpret_cast<const char*>(data), size, &status);
  if (U_FAILURE(status)) {
    return 0;
  }

  int flags = stream.ConsumeIntegral<int>();
  matcher.~RegexMatcher();  // Call destructor for the previous object.
  new (&matcher) icu_66::RegexMatcher(utext, flags, &status);  // Placement new.

  utext_close(utext);

  return 0;
}