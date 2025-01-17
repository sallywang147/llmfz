#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "rapidjson/document.h"
#include "valijson/adapters/rapidjson_adapter.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  rapidjson::Document doc;
  std::string json_string = stream.ConsumeRemainingBytesAsString();

  if (doc.Parse(json_string.c_str()).HasParseError()) {
    return 0;
  }

  valijson::adapters::RapidJsonAdapter doc_adapter(doc);
  valijson::adapters::GenericRapidJsonFrozenValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > frozen_value(&doc_adapter, doc);

  return 0;
}