#include "oatpp/parser/json/mapping/Serializer.hpp"
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
  oatpp::parser::json::mapping::ObjectMapper mapper;
  oatpp::Object<Test1> obj = mapper.readFromString<oatpp::Object<Test1>>(input);
  if (obj) {
    Serializer serializer;
    serializer.serializeObject(obj.get(), nullptr, nullptr);
  }

  return 0;
}

#include OATPP_CODEGEN_END

extern "C" {
#include OATPP_CODEGEN(DTO)
}