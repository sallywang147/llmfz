#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "oatpp/parser/json/mapping/Serializer.hpp"
#include "oatpp/core/data/mapping/type/Type.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create serializer object
  oatpp::parser::json::mapping::Serializer serializer;

  // Create bad_array_new_length object
  std::bad_array_new_length bad_array_new_length;

  // Create Void object
  oatpp::data::mapping::type::Void voidObj;

  // Call the function to fuzz
  serializer.serializeMap(&serializer, &bad_array_new_length, &voidObj);

  return 0;
}