#include <oatpp/core/data/string/String.hpp>
#include <oatpp/parser/json/mapping/Deserializer.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/parser/json/mapping/Serializer.hpp>
#include <oatpp/parser/Caret.hpp>
#include <oatpp/core/data/mapping/type/Void.hpp>

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
  try {
    deserializer.deserializeAny(nullptr, &deserializer, &ParsingCaret(input),
                               oatpp::data::mapping::type::Void::getType());
  } catch (...) {
    std::cout << "Exception: " << std::current_exception() << '\n';
  }

  return 0;
}

#include OATPP_CODEGEN_END