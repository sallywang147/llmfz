#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "valijson/adapters/rapidjson_adapter.hpp"
#include "valijson/adapters/rapidjson_value.hpp"
#include "valijson/utils/rapidjson_utils.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  rapidjson::Document d;
  d.Parse(reinterpret_cast<char *>(bytes.data()), bytes.size());

  valijson::adapters::RapidJsonAdapter adapter(d);
  valijson::adapters::GenericRapidJsonArrayValueIterator it(adapter);
  valijson::adapters::GenericRapidJsonValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > value(
      *it);
  value.freeze(&it);
  return 0;
}