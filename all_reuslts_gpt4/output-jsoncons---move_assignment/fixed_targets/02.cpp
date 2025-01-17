#include <fuzzer/FuzzedDataProvider.h>
#include <jsoncons/json.hpp>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create two json objects
  jsoncons::basic_json<char, jsoncons::order_preserving_policy, std::allocator<char>> json1;
  jsoncons::basic_json<char, jsoncons::order_preserving_policy, std::allocator<char>> json2;

  // Populate the first json object with data
  std::string jsonString1 = stream.ConsumeRandomLengthString();
  try {
    json1 = jsoncons::json::parse(jsonString1);
  } catch (jsoncons::json_exception&) {
    // Ignore parsing errors
  }

  // Populate the second json object with data
  std::string jsonString2 = stream.ConsumeRemainingBytesAsString();
  try {
    json2 = jsoncons::json::parse(jsonString2);
  } catch (jsoncons::json_exception&) {
    // Ignore parsing errors
  }

  // Perform the move assignment
  json1.move_assignment(&json2);

  return 0;
}