#include <boost/regex.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fuzzed_data(Data, Size);
  std::string regex_string = fuzzed_data.ConsumeRemainingBytesAsString();
  boost::re_detail_500::basic_regex_parser<char, boost::c_regex_traits<char> > parser;
  parser.parse_extended(&parser);
  return 0;
}