#include <valijson/valijson.hpp>
#include <valijson/adapters/rapidjson_adapter.hpp>
#include <rapidjson/document.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  rapidjson::Document document;
  document.Parse(reinterpret_cast<const char *>(data), size);

  valijson::adapters::GenericRapidJsonFrozenValue<
      rapidjson::GenericValue<rapidjson::UTF8<char>,
                             rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>>
      genericRapidJsonFrozenValue;
  valijson::adapters::GenericRapidJsonFrozenValue<
      rapidjson::GenericValue<rapidjson::UTF8<char>,
                             rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>>
      *genericRapidJsonFrozenValuePtr = &genericRapidJsonFrozenValue;

  genericRapidJsonFrozenValuePtr->GenericRapidJsonFrozenValue(
      genericRapidJsonFrozenValuePtr, &document);
  return 0;
}