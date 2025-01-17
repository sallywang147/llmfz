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
  boost::json::operator>>(ss, &jv);  // Fix: remove std::addressof()
  return 0;
}