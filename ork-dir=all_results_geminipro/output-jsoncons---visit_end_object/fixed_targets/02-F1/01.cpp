#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "jsoncons/json.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input_json = stream.ConsumeRemainingBytesAsString();
  jsoncons::json_decoder<jsoncons::basic_json<char, jsoncons::order_preserving_policy, std::__1::allocator<char> >, std::__1::allocator<char> > decoder;
  jsoncons::json_decoder::error_handler eh;
  jsoncons::json_decoder::visit_handler vh;
  bool result = decoder.visit_end_object(&eh, &vh, input_json.c_str(), input_json.c_str() + input_json.size());
  return result;
}