#include <fuzzer/FuzzedDataProvider.h>
#include <boost/regex.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  // First value is length of the regex string
  size_t regex_length = stream.ConsumeIntegral<uint8_t>();
  // Second value is regexp string whose length is `regex_length`
  std::string regex_string = stream.ConsumeBytesAsString(regex_length);
  try {
    boost::regex parser(regex_string);
    parser.parse_basic_escape();
  }
  catch (const std::runtime_error &) {
  }
  return 0;
}