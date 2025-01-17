#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <oatpp/parser/json/mapping/Deserializer.hpp>
#include <oatpp/core/data/mapping/type/Type.hpp>
#include <oatpp/core/parser/Caret.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    oatpp::parser::json::mapping::Deserializer deserializer;
    oatpp::data::mapping::type::Type* type = oatpp::data::mapping::type::Type::createShared();
    oatpp::data::mapping::type::Void* voidObject = type->instantiate();
    oatpp::String jsonString = stream.ConsumeRemainingBytesAsString().c_str();
    oatpp::parser::Caret caret(jsonString);

    deserializer.deserializeMap(voidObject.get(), &deserializer, &caret, type.get());

    return 0;
}