#include <boost/json/json_spirit.hpp>
#include <boost/json/parser.hpp>
#include <boost/json/value.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string json_string = provider.ConsumeRemainingBytesAsString();
  std::istringstream stream(json_string);
  boost::json::value value;
  boost::json::read(stream, value); // Call the `read` function to parse the JSON string
  return 0;
}