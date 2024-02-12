#include <fuzzer/FuzzedDataProvider.h>
#include <boost/regex/pattern_except.hpp>

extern "C" {
#include <boost/regex/regex_parser.hpp>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fuzzed_data(Data, Size);
  size_t regex_length = fuzzed_data.ConsumeIntegral<uint8_t>();
  std::string regex_string = fuzzed_data.ConsumeBytesAsString(regex_length);
  try {
    boost::re_detail_500::basic_regex_parser<char, boost::regex_traits<char, boost::cpp_regex_traits<char> > > parser;
    parser.parse_basic(regex_string.c_str());
  }
  catch (boost::regex_error &) {
  }
  return 0;
}