#include <fuzzer/FuzzedDataProvider.h>
#include <valijson/adapters/rapidjson_adapter.hpp>
#include <rapidjson/document.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a RapidJson Document
  rapidjson::Document document;

  // Parse JSON from the fuzzed data
  std::string json = stream.ConsumeRemainingBytesAsString();
  if (document.Parse(json.c_str()).HasParseError()) {
    return 0;
  }

  // Create a Valijson adapter for the RapidJson document
  valijson::adapters::RapidJsonAdapter adapter(document);

  // Create a GenericRapidJsonFrozenValue object
  valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > frozenValue(&adapter);

  // Clone the GenericRapidJsonFrozenValue object
  std::unique_ptr<valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > > clonedFrozenValue(static_cast<valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > >*>(frozenValue.clone()));

  return 0;
}