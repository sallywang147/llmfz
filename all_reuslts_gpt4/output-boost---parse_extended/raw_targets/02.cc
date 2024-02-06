#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <boost/regex/v4/basic_regex_parser.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();

  try {
    boost::re_detail_500::basic_regex_parser<char, boost::c_regex_traits<char>> parser(str);
    parser.parse_extended(&parser);
  } catch (...) {
    // Catch all exceptions
  }

  return 0;
}