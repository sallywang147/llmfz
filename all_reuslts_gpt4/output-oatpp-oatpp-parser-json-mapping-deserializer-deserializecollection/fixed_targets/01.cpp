#include <fuzzer/FuzzedDataProvider.h>
#include "oatpp/parser/json/mapping/Deserializer.hpp"
#include "oatpp/core/data/mapping/type/Type.hpp"
#include "oatpp/core/parser/Caret.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  oatpp::parser::json::mapping::Deserializer deserializer;
  oatpp::parser::Caret caret(stream.ConsumeRandomLengthString().c_str());
  oatpp::data::mapping::type::Type* type = oatpp::data::mapping::type::__class::String::getType();

  oatpp::data::mapping::type::Void* collection = oatpp::data::mapping::type::__class::AbstractList::createShared();

  deserializer.deserializeCollection(collection, &deserializer, &caret, type);

  return 0;
}