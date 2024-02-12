#include <boost/regex.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fuzzed_data(Data, Size);
  // First value is length of the regex string
  size_t regex_length = fuzzed_data.ConsumeIntegral<uint8_t>();
  // Second value is regexp string whose length is `regex_length`
  std::string regex_string = fuzzed_data.ConsumeBytesAsString(regex_length);
  boost::regex_data<char, boost::c_regex_traits<char> > regex_data(regex_string);
  try {
    boost::basic_regex_parser<char, boost::c_regex_traits<char> > parser(&regex_data);
    bool match = parser.parse_extended();
  }
  catch (const std::runtime_error &) {
  }
  return 0;
}