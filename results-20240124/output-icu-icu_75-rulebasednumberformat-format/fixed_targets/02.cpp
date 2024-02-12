#include <stddef.h>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <string>

extern "C" {
#include <unicode/rbnf.h>
#include <unicode/ustring.h>
}

using namespace std;

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  UErrorCode status = U_ZERO_ERROR;
  icu::UnicodeString pattern((const char*)data, size - 1);
  icu::RuleBasedNumberFormat* fmt = icu::RuleBasedNumberFormat::createInstance(pattern, icu::Locale::getUS(), status);
  if (U_FAILURE(status)) {
    return 0;
  }

  icu::UnicodeString output;
  fmt->format(123456789, output, status);
  if (U_FAILURE(status)) {
    return 0;
  }

  cout << output << endl;
  return 0;
}