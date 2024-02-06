#include <fuzzer/FuzzedDataProvider.h>
#include "oatpp/parser/json/mapping/Deserializer.hpp"
#include "oatpp/core/data/mapping/type/Type.hpp"
#include "oatpp/core/parser/Caret.hpp"
#include "oatpp/core/base/Environment.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    oatpp::base::Environment::init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Prepare the parameters for the function.
  oatpp::parser::json::mapping::Deserializer deserializer;
  oatpp::parser::Caret caret(stream.ConsumeRandomLengthString());
  oatpp::data::mapping::type::Type* type = oatpp::data::mapping::type::__class::String::getType();

  // Call the function with the prepared parameters.
  deserializer.deserializeAny(nullptr, &deserializer, &caret, type);

  return 0;
}