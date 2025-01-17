#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "valijson/adapters/basic_adapter.hpp"
#include "valijson/adapters/generic_rapid_json_adapter.hpp"
#include "valijson/adapters/generic_rapid_json_array.hpp"
#include "valijson/adapters/generic_rapid_json_json_value.hpp"
#include "valijson/adapters/generic_rapid_json_member.hpp"
#include "valijson/adapters/generic_rapid_json_object.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string json_string = stream.ConsumeRemainingBytesAsString();
  rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> json_value;
  rapidjson::ParseResult result = json_value.Parse(json_string.c_str());
  if (result.IsError()) {
    return 0;
  }

  valijson::adapters::BasicAdapter<
      valijson::adapters::GenericRapidJsonAdapter<rapidjson::GenericValue<
          rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonArray<rapidjson::GenericValue<
          rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonObjectMember<rapidjson::GenericValue<
          rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonObject<rapidjson::GenericValue<
          rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonValue<rapidjson::GenericValue<
          rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>>>
          > adapter;

  std::string key = stream.ConsumeRemainingBytesAsString();
  bool result_comparison = adapter.ObjectComparisonFunctor()(nullptr, &key, nullptr);

  return result_comparison;
}