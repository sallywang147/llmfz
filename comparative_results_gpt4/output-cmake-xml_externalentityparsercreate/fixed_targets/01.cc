#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a base parser
  XML_Parser parser = XML_ParserCreate(nullptr);
  if (!parser) {
    return 0;
  }

  // Split the input data into two strings
  std::string str1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  // Create an external entity parser
  XML_Parser ext_parser = XML_ExternalEntityParserCreate(parser, str1.c_str(), str2.c_str());
  if (ext_parser) {
    XML_ParserFree(ext_parser);
  }

  XML_ParserFree(parser);
  return 0;
}