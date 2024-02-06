#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <boost/regex/v4/basic_regex_parser.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  boost::re_detail_500::basic_regex_parser<char, boost::regex_traits<char, boost::cpp_regex_traits<char> > > parser;
  parser.parse_basic_escape(&parser);

  return 0;
}