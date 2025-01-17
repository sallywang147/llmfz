#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "oatpp/parser/json/mapping/Deserializer.hpp"
#include "oatpp/core/data/mapping/type/Type.hpp"
#include "oatpp/core/parser/Caret.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string input = stream.ConsumeRemainingBytesAsString();

  oatpp::parser::Caret caret(input.c_str());

  oatpp::data::mapping::type::Type* type = oatpp::data::mapping::type::__class::String::getType();
  oatpp::data::mapping::type::Void* object = nullptr;

  oatpp::parser::json::mapping::Deserializer deserializer;

  deserializer.deserializeAny(object, &deserializer, &caret, type);

  return 0;
}