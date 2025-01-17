#include <iostream>
#include <string>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <unicode/rbnf.h>
}

UnicodeString *format(RuleBasedNumberFormat *rbnf, size_t number, UnicodeString *ruleSetName, UnicodeString *toAppendTo, FieldPosition *fp, int *status) {
  return rbnf->format(number, ruleSetName, toAppendTo, fp, status);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  UnicodeString ruleSetName = fuzzed_data.ConsumeUnicodeString(size);
  UnicodeString toAppendTo = fuzzed_data.ConsumeUnicodeString(size);
  UnicodeString number = fuzzed_data.ConsumeUnicodeString(size);
  RuleBasedNumberFormat rbnf(ruleSetName);
  int status = 0;
  FieldPosition fp;
  UnicodeString *result = format(&rbnf, atoi(number.toUTF8().getBuffer()), &ruleSetName, &toAppendTo, &fp, &status);
  if (result) {
    std::cout << result->toUTF8().getBuffer() << std::endl;
    delete result;
  }
  return 0;
}