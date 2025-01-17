#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "valijson/adapters/rapidjson_adapter.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  rapidjson::Document document;
  document.Parse(reinterpret_cast<const char *>(data), size);

  if (document.HasParseError()) {
    return 0;
  }

  valijson::adapters::RapidJsonAdapter adapter(document);
  
  if (!adapter.isArray()) {
    return 0;
  }

  auto it = adapter.begin();
  if (it == adapter.end()) {
    return 0;
  }

  valijson::adapters::GenericRapidJsonArrayValueIterator<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>> iterator(it);

  adapter.freeze(&iterator);

  return 0;
}