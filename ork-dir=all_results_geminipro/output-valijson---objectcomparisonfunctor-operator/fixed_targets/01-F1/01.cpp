#include <fuzzer/FuzzedDataProvider.h>

#include <memory>
#include <string>
#include <vector>

#include "valijson/adapters/basic_adapter.hpp"
#include "valijson/adapters/generic_rapid_json_adapter.hpp"
#include "valijson/adapters/generic_rapid_json_array.hpp"
#include "valijson/adapters/generic_rapid_json_object.hpp"
#include "valijson/adapters/generic_rapid_json_object_member.hpp"
#include "valijson/adapters/generic_rapid_json_value.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::vector<uint8_t> value_bytes = stream.ConsumeRemainingBytes();
  rapidjson::GenericValue<rapidjson::UTF8<char>,
                         rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>
      value;
  value.Parse<0>(reinterpret_cast<const char*>(value_bytes.data()));

  const std::string key = stream.ConsumeRemainingBytesAsString();

  valijson::adapters::BasicAdapter<
      valijson::adapters::GenericRapidJsonAdapter<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonArray<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonObjectMember<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonObject<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonValue<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>>
      adapter;

  valijson::adapters::BasicAdapter<
      valijson::adapters::GenericRapidJsonAdapter<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonArray<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonObjectMember<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonObject<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>,
      valijson::adapters::GenericRapidJsonValue<
          rapidjson::GenericValue<rapidjson::UTF8<char>,
                                 rapidjson::MemoryPoolAllocator<
                                     rapidjson::CrtAllocator>>>>>
      other_adapter;

  adapter.ObjectComparisonFunctor::operator()(
      &other_adapter.ObjectComparisonFunctor, &key, nullptr);

  return 0;
}