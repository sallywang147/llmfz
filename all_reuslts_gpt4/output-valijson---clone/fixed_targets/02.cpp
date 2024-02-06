#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "valijson/adapters/rapidjson_adapter.hpp"
#include "rapidjson/document.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a rapidjson document
  rapidjson::Document document;

  // Parse the input data into the document
  document.Parse(reinterpret_cast<const char*>(data), size);

  // Check if the document has parse errors
  if (document.HasParseError()) {
    return 0;
  }

  // Create a GenericRapidJsonFrozenValue from the document
  valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::Document> originalFrozenValue(document);

  // Clone the GenericRapidJsonFrozenValue
  std::unique_ptr<valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::Document>> clonedFrozenValue;
  clonedFrozenValue.reset(static_cast<valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::Document>*>(originalFrozenValue.clone()));

  return 0;
}