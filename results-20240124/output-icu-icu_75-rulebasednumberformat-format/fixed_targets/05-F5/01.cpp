#include <unicode/unistr.h>
#include <unicode/rbnf.h>

extern "C" {
#include <unicode/numfmt.h>
}

int main() {
  UnicodeString pattern("#,##0.00");
  RuleBasedNumberFormat fmt(pattern, Locale::getUS());
  UnicodeString result;
  fmt.format(123456789, result);
  printf("%s\n", result.getBuffer());
  return 0;
}