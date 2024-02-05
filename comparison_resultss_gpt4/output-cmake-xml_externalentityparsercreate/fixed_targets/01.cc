#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct XML_ParserStruct *parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  std::string context = stream.ConsumeRandomLengthString();
  std::string encoding = stream.ConsumeRandomLengthString();

  struct XML_ParserStruct *entityParser = XML_ExternalEntityParserCreate(parser, context.c_str(), encoding.c_str());

  XML_ParserFree(parser);
  if (entityParser) {
    XML_ParserFree(entityParser);
  }

  return 0;
}