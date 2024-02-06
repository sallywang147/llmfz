#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "oatpp/parser/json/mapping/Serializer.hpp"
#include "oatpp/core/data/mapping/type/Primitive.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize Serializer object
  oatpp::parser::json::mapping::Serializer serializer;
  
  // Initialize bad_array_new_length object
  std::bad_array_new_length bad_array_new_length_obj;
  
  // Initialize Void object
  oatpp::data::mapping::type::Void void_obj;
  
  // Call the target function
  serializer.serializeMap(&serializer, &bad_array_new_length_obj, &void_obj);

  return 0;
}