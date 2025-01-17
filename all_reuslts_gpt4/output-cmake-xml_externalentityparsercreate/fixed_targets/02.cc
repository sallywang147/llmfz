#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a new XML parser
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  // Create two strings from the data
  std::string context = stream.ConsumeRandomLengthString();
  std::string encoding = stream.ConsumeRemainingBytesAsString();

  // Create an external entity parser
  XML_Parser ext_parser = XML_ExternalEntityParserCreate(parser, context.c_str(), encoding.c_str());
  if (!ext_parser) {
    XML_ParserFree(parser);
    return 0;
  }

  // Free the parsers
  XML_ParserFree(ext_parser);
  XML_ParserFree(parser);

  return 0;
}