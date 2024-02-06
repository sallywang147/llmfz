#include <fuzzer/FuzzedDataProvider.h>
#include <oatpp/parser/json/mapping/Deserializer.hpp>
#include <oatpp/core/data/mapping/type/Type.hpp>
#include <oatpp/core/parser/Caret.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if(size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  oatpp::parser::json::mapping::Deserializer deserializer;
  oatpp::parser::Caret caret(stream.ConsumeRandomLengthString().c_str());
  oatpp::data::mapping::type::Type* type = oatpp::data::mapping::type::__class::String::getType();

  // We need to pass a valid object to be deserialized into. In this case, we are deserializing a collection of strings.
  // Therefore, we pass an object of type List<String>.
  auto collection = oatpp::data::mapping::type::AbstractList::createShared();
  oatpp::data::mapping::type::Void* collectionVoid = collection.get();

  deserializer.deserializeCollection(collectionVoid, &deserializer, &caret, type);

  return 0;
}