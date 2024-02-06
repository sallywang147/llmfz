#include <fuzzer/FuzzedDataProvider.h>
#include <unicode/rbnf.h>
#include <unicode/unistr.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  UErrorCode status = U_ZERO_ERROR;
  icu_75::RuleBasedNumberFormat rbnf(icu_75::URBNFRuleSetTag::URBNF_SPELLOUT, icu_75::Locale::getUS(), status);
  if (U_FAILURE(status)) {
    return 0;
  }

  size_t number = fuzzed_data.ConsumeIntegral<size_t>();
  std::string rule_set_name = fuzzed_data.ConsumeRemainingBytesAsString();
  icu_75::UnicodeString unicode_rule_set_name(rule_set_name.c_str(), rule_set_name.size());
  icu_75::UnicodeString to_append_to;
  icu_75::FieldPosition field_position;

  rbnf.format(number, &unicode_rule_set_name, &to_append_to, &field_position, &status);

  return 0;
}