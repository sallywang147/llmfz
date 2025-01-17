#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <boost/regex/v4/basic_regex_parser.hpp>
#include <boost/regex/v4/c_regex_traits.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

  FuzzedDataProvider fuzzed_data(data, size);

  // Create a basic_regex_parser object
  boost::re_detail_500::basic_regex_parser<char, boost::c_regex_traits<char>> parser;

  // Call parse_extended function with the created basic_regex_parser object
  bool result = parser.parse_extended(&parser);

  return 0;
}