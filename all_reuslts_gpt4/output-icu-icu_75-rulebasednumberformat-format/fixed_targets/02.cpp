#include <fuzzer/FuzzedDataProvider.h>
#include <unicode/numfmt.h>
#include <unicode/unistr.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  UErrorCode status = U_ZERO_ERROR;
  icu_75::RuleBasedNumberFormat rbnf(icu_75::URBNF_SPELLOUT, icu_75::Locale::getEnglish(), status);
  if (U_FAILURE(status)) {
    return 0;
  }
  
  size_t number = stream.ConsumeIntegral<size_t>();
  icu_75::UnicodeString ruleSetName = icu_75::UnicodeString::fromUTF8(stream.ConsumeRandomLengthString().c_str());
  icu_75::UnicodeString toAppendTo;
  icu_75::FieldPosition fieldPosition;

  rbnf.format(number, ruleSetName, toAppendTo, &fieldPosition, &status);

  return 0;
}