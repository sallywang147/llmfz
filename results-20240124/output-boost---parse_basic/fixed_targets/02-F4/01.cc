#include <fuzzer/FuzzedDataProvider.h>
#include <boost/regex/v5/regex_parser.hpp>
#include <boost/regex/v5/regex_parser/parse_basic.hpp>
#include <boost/regex/v5/regex_traits.hpp>
#include <boost/regex/v5/cpp_regex_traits.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  // First value is length of the regex string
  size_t regex_length = fuzzed_data.ConsumeIntegral<uint8_t>();
  // Second value is regexp string whose length is `regex_length`
  std::string regex_string = fuzzed_data.ConsumeBytesAsString(regex_length);
  try {
    boost::re_detail_500::basic_regex_parser<char,
        boost::regex_traits<char, boost::cpp_regex_traits<char> > > parser;
    boost::re_detail_500::parse_basic(parser, regex_string.c_str());
  } catch (const std::runtime_error &) {
  }
  return 0;
}