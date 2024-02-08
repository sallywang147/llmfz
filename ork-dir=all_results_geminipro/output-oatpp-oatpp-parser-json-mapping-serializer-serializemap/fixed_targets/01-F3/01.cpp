#include <cstdio>
#include <cstring>
#include <vector>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/Deserializer.hpp"
#include "oatpp/parser/json/mapping/Serializer.hpp"

typedef oatpp::parser::Caret ParsingCaret;
typedef oatpp::parser::json::mapping::Serializer Serializer;
typedef oatpp::parser::json::mapping::Deserializer Deserializer;

extern "C" {
#include OATPP_CODEGEN_BEGIN(DTO)

class EmptyDto : public oatpp::DTO {
  DTO_INIT(EmptyDto, DTO)
};

class Test1 : public oatpp::DTO {
  DTO_INIT(Test1, DTO)
  DTO_FIELD(String, strF);
};

}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  oatpp::String input(reinterpret_cast<const char *>(data), size);
  oatpp::parser::json::mapping::ObjectMapper mapper;
  oatpp::Object<Test1> obj;
  try {
    obj = mapper.readFromString<oatpp::Object<Test1>>(input);
  } catch (...) {
    return 0;
  }

  Serializer serializer;
  std::vector<oatpp::String> str;
  serializer.serializeMap(nullptr, &str, obj.get());

  return 0;
}

#include OATPP_CODEGEN_END