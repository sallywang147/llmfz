#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" {
#include <unicode/unistr.h>
#include <unicode/rbnf.h>
}

using namespace std;

UnicodeString *format(RuleBasedNumberFormat *this, size_t number, UnicodeString *ruleSetName, UnicodeString *toAppendTo, FieldPosition *pos, int *status) const {
  return this->format(number, ruleSetName, toAppendTo, pos, status);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  UnicodeString input(TRUE, (UChar *)data, size / sizeof(UChar));
  UErrorCode status = U_ZERO_ERROR;
  RuleBasedNumberFormat *formatter = new RuleBasedNumberFormat(input, status);
  if (U_SUCCESS(status)) {
    UnicodeString result;
    format(formatter, 123456789, NULL, &result, NULL, &status);
    if (U_SUCCESS(status)) {
      // Do something with the result.
    }
    delete formatter;
  }
  return 0;
}