#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "unicode/regex.h"
#include "unicode/unistr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  icu::UnicodeString input(text.c_str(), text.size());

  icu::RegexMatcher matcher(input, 0);
  int status = 0;
  matcher.RegexMatcher(nullptr, 0, &status);
  return 0;
}