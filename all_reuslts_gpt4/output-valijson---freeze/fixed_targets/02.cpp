#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "valijson/adapters/rapidjson_adapter.hpp"
#include "valijson/utils/rapidjson_utils.hpp"
#include "rapidjson/document.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  // Create a RapidJson Document
  rapidjson::Document document;
  std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();
  if (document.Parse(json_string.c_str()).HasParseError()) {
    return 0;
  }

  // Create a RapidJson Value
  rapidjson::Value value;
  if (!document.IsArray()) {
    return 0;
  }

  // Create a RapidJson Value Iterator
  rapidjson::Value::ValueIterator iterator = document.GetArray().Begin();

  // Create a GenericRapidJsonValue
  valijson::adapters::RapidJsonAdapter generic_rapid_json_value(value);

  // Create a GenericRapidJsonArrayValueIterator
  valijson::adapters::RapidJsonArrayValue::iterator generic_rapid_json_array_value_iterator(iterator);

  // Call the freeze function
  std::unique_ptr<valijson::adapters::Adapter> frozen_value = generic_rapid_json_value.freeze(&generic_rapid_json_array_value_iterator);

  return 0;
}