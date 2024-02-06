#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include <rapidjson/document.h>
#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/utils/rapidjson_utils.hpp>

using valijson::adapters::GenericRapidJsonFrozenValue;
using valijson::adapters::RapidJsonAdapter;
using rapidjson::GenericValue;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input_file(reinterpret_cast<const char *>(data), size);
  rapidjson::Document document;
  if (!valijson::utils::loadDocument(input_file, document)) {
    return 0;
  }

  RapidJsonAdapter adapter(document);
  GenericValue *value = adapter.getValue();
  GenericRapidJsonFrozenValue<GenericValue> frozen_value(nullptr, value);

  return 0;
}