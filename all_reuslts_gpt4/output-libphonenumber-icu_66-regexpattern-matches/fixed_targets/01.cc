#include <fuzzer/FuzzedDataProvider.h>
#include <unicode/regex.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  
  UErrorCode status = U_ZERO_ERROR;
  UParseError parse_error;
  
  std::string regex_string = fuzzed_data.ConsumeRandomLengthString();
  std::string input_string = fuzzed_data.ConsumeRemainingBytesAsString();
  
  UText* regex_utext = utext_openUTF8(nullptr, regex_string.c_str(), regex_string.length(), &status);
  UText* input_utext = utext_openUTF8(nullptr, input_string.c_str(), input_string.length(), &status);
  
  if (U_FAILURE(status)) {
    utext_close(regex_utext);
    utext_close(input_utext);
    return 0;
  }
  
  icu_66::RegexPattern* pattern = icu_66::RegexPattern::compile(regex_utext, 0, parse_error, status);
  
  if (U_FAILURE(status)) {
    utext_close(regex_utext);
    utext_close(input_utext);
    delete pattern;
    return 0;
  }
  
  pattern->matches(input_utext, parse_error, &status);
  
  utext_close(regex_utext);
  utext_close(input_utext);
  delete pattern;
  
  return 0;
}