#include <boost/regex.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <regex>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fuzzed_data(Data, Size);

  // First value is length of the regex string
  size_t regex_length = fuzzed_data.ConsumeIntegral<uint8_t>();
  // Second value is regexp string whose length is `regex_length`
  std::string regex_string = fuzzed_data.ConsumeBytesAsString(regex_length);

  // Parse the regular expression string
  boost::re_detail_500::basic_regex_parser<wchar_t, boost::c_regex_traits<wchar_t> > parser;
  parser.parse_basic(&parser);  // Call parse_basic explicitly
  parser.parse(regex_string.c_str(), regex_string.c_str() + regex_length);

  // Compile the regular expression
  std::regex regex(regex_string.c_str());

  return 0;
}