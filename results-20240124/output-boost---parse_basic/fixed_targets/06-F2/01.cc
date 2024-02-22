#include <fuzzer/FuzzedDataProvider.h>
#include <boost/regex.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fuzzed_data(Data, Size);
  // First value is length of the regex string
  size_t regex_length = fuzzed_data.ConsumeIntegral<uint8_t>();
  // Second value is regexp string whose length is `regex_length`
  std::string regex_string = fuzzed_data.ConsumeBytesAsString(regex_length);
  try {
    boost::regex_parser<char, boost::regex_traits<char, boost::cpp_regex_traits<char> > > parser;
    parser.parse_basic(&parser);
  }
  catch (const std::runtime_error &) {
  }
  return 0;
}