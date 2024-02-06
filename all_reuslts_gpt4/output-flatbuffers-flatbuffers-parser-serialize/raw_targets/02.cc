#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  flatbuffers::Parser parser;
  FuzzedDataProvider provider(data, size);
  std::string schema = provider.ConsumeRandomLengthString();
  std::string json = provider.ConsumeRemainingBytesAsString();

  if (parser.Parse(schema.c_str()) && parser.Parse(json.c_str())) {
    flatbuffers::Parser parser2;
    parser2.Parse(schema.c_str());
    parser.Serialize(&parser2);
  }

  return 0;
}