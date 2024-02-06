#include <fuzzer/FuzzedDataProvider.h>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/idl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  flatbuffers::Parser parser;

  FuzzedDataProvider stream(data, size);
  std::string schema = stream.ConsumeRandomLengthString();
  std::string json = stream.ConsumeRemainingBytesAsString();

  if (parser.Parse(schema.c_str()) && parser.Parse(json.c_str())) {
    flatbuffers::Parser parser2;
    parser.Serialize(&parser2);
  }

  return 0;
}