 #include <fuzzer/FuzzedDataProvider.h>

#include <boost/regex.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fuzzed_data(Data, Size);

  boost::re_detail_500::basic_regex_parser<char, boost::regex_traits<char, boost::cpp_regex_traits<char> > > parser;
  boost::re_detail_500::basic_regex_parser<char, boost::regex_traits<char, boost::cpp_regex_traits<char> > >::parse_basic_escape(&parser);

  return 0;
}