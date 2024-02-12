#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <unicode/rbnf.h>
}

UnicodeString *format(RuleBasedNumberFormat *this, size_t number, UnicodeString *ruleSetName, UnicodeString *toAppendTo, FieldPosition *pos, int *status) const {
  return this->format(number, ruleSetName, toAppendTo, pos, status);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  RuleBasedNumberFormat *rbnf = rbnf_create(fdp.ConsumeRandomLengthString().c_str(), ULOC_ENGLISH, status);
  if (rbnf == nullptr) {
    return 0;
  }
  UnicodeString number = fdp.ConsumeUnicodeString(10);
  UnicodeString ruleSetName = fdp.ConsumeUnicodeString(10);
  UnicodeString toAppendTo;
  format(rbnf, number, &ruleSetName, &toAppendTo, nullptr, status);
  rbnf_delete(rbnf);
  return 0;
}