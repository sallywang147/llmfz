#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create the main parser
  XML_Parser main_parser = XML_ParserCreate(NULL);
  if (!main_parser) {
    return 0;
  }

  // Consume data for the external entity parser
  std::string context = stream.ConsumeRandomLengthString();
  std::string encoding = stream.ConsumeRemainingBytesAsString();

  // Create the external entity parser
  XML_Parser ext_parser = XML_ExternalEntityParserCreate(main_parser, context.c_str(), encoding.c_str());
  if (ext_parser) {
    XML_ParserFree(ext_parser);
  }

  XML_ParserFree(main_parser);
  return 0;
}