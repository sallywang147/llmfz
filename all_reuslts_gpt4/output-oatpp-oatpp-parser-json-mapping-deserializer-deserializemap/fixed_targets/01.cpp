#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "oatpp/parser/json/mapping/Deserializer.hpp"
#include "oatpp/core/data/mapping/type/Type.hpp"
#include "oatpp/core/parser/Caret.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a Deserializer instance
  oatpp::parser::json::mapping::Deserializer deserializer;

  // Create a Caret from the fuzzed data
  std::string jsonData = stream.ConsumeRemainingBytesAsString();
  oatpp::parser::Caret caret(jsonData);

  // Create a Void object
  oatpp::data::mapping::type::Void obj;

  // Create a Type object
  oatpp::data::mapping::type::Type type;

  // Call the function to be fuzzed
  deserializer.deserializeMap(&obj, &deserializer, &caret, &type);

  return 0;
}