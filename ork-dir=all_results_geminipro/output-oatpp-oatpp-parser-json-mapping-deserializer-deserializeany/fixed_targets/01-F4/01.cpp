#include "oatpp/parser/json/mapping/Deserializer.hpp"
#include "oatpp/core/macro/codegen.hpp"

typedef oatpp::parser::Caret ParsingCaret;
typedef oatpp::parser::json::mapping::Serializer Serializer;
typedef oatpp::parser::json::mapping::Deserializer Deserializer;

#include OATPP_CODEGEN_BEGIN(DTO)

class EmptyDto : public oatpp::DTO {
  DTO_INIT(EmptyDto, DTO)
};

class Test1 : public oatpp::DTO {
  DTO_INIT(Test1, DTO)
  DTO_FIELD(String, strF);
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  oatpp::String input(reinterpret_cast<const char *>(data), size);
  oatpp::parser::json::mapping::Deserializer deserializer;
  oatpp::parser::json::mapping::Type type = oatpp::parser::json::mapping::Type::create<oatpp::Void>();
  try {
    deserializer.deserializeAny(&type, &deserializer, &ParsingCaret::createShared(), &type);
  } catch (...) {
  }

  return 0;
}

#include OATPP_CODEGEN_END