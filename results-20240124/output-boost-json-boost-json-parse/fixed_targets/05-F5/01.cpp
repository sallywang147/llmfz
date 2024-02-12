#include <stdint.h>
#include <stddef.h>
#include <boost/json.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();
  boost::json::value json_value;
  boost::json::error_code error_code;
  boost::json::parse(&json_value, const_cast<char*>(json_string.c_str()), json_string.size(), error_code);
  return 0;
}