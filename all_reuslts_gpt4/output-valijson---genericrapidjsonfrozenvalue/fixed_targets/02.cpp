#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "valijson/adapters/rapidjson_adapter.hpp"
#include "rapidjson/document.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a RapidJSON document
  rapidjson::Document doc;

  // Consume data as a string and parse it into the RapidJSON document
  std::string jsonString = provider.ConsumeRemainingBytesAsString();
  doc.Parse(jsonString.c_str());

  // If the document has parse errors, we're done
  if (doc.HasParseError()) {
    return 0;
  }

  // Create a Valijson adapter for the RapidJSON document
  valijson::adapters::RapidJsonAdapter docAdapter(doc);

  // Create a frozen value from the adapter
  std::unique_ptr<valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > > frozenValue(new valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > >(&docAdapter, doc));

  return 0;
}