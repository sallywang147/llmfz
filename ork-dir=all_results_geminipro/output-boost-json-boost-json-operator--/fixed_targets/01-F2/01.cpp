#include <boost/json.hpp>
#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>

extern "C" {
#include <sstream>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string json_input = provider.ConsumeRemainingBytesAsString();
  std::stringstream ss(json_input);
  boost::json::value jv;
  boost::json::operator>>(std::addressof(ss), std::addressof(jv));
  return 0;
}