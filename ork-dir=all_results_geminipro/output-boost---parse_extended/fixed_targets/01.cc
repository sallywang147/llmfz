#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <boost/regex/v5/regex_parser.hpp>
#include <boost/regex/v5/regex_traits.hpp>
}

namespace boost {
namespace re_detail_500 {
class basic_regex_parser;
}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fuzzed_data(Data, Size);
  // First value is length of the regex string
  size_t regex_length = fuzzed_data.ConsumeIntegral<uint8_t>();
  // Second value is regexp string whose length is `regex_length`
  std::string regex_string = fuzzed_data.ConsumeBytesAsString(regex_length);

#ifdef DEBUG
  std::cout << "Regexp string: " << regex_string << "Size: " << regex_string.size() << std::endl;
#endif

  try {
    boost::re_detail_500::basic_regex_parser<char, boost::c_regex_traits<char> > parser;
    bool result = parser.parse_extended(&regex_string);
    if (result) {
      std::cout << "Regex string parsed successfully." << std::endl;
    } else {
      std::cout << "Regex string could not be parsed." << std::endl;
    }
  } catch (const std::runtime_error &) {
    std::cout << "Regex string caused a runtime error." << std::endl;
  }
  return 0;
}