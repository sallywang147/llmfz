#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "oatpp/parser/json/mapping/Serializer.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Serializer
  oatpp::parser::json::mapping::Serializer serializer;

  // Initialize std::bad_array_new_length object
  std::bad_array_new_length bad_array_new_length_obj;

  // Initialize oatpp::data::mapping::type::Void object
  oatpp::data::mapping::type::Void void_obj;

  // Call the function to fuzz
  serializer.serializeObject(&serializer, &bad_array_new_length_obj, &void_obj);

  return 0;
}