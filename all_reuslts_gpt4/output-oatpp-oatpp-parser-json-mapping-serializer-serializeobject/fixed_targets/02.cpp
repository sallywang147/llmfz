#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "oatpp/parser/json/mapping/Serializer.hpp"
#include "oatpp/core/data/mapping/type/Type.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  oatpp::parser::json::mapping::Serializer serializer;
  std::bad_array_new_length bad_array_new_length;
  oatpp::data::mapping::type::Void voidType;

  serializer.serializeObject(&serializer, &bad_array_new_length, &voidType);

  return 0;
}