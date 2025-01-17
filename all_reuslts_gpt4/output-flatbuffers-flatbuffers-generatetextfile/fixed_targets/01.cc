#include <fuzzer/FuzzedDataProvider.h>
#include <flatbuffers/idl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  flatbuffers::Parser parser;
  FuzzedDataProvider stream(data, size);
  
  std::string schema = stream.ConsumeRandomLengthString();
  std::string json = stream.ConsumeRemainingBytesAsString();

  if (!parser.Parse(schema.c_str())) {
    return 0;
  }

  if (!parser.Parse(json.c_str())) {
    return 0;
  }

  char *textfile = flatbuffers::GenerateTextFile(&parser, &schema, &json);

  delete[] textfile;

  return 0;
}