#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  // Divide the data into two parts to be used as parameters for the function
  std::string param1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string param2 = stream.ConsumeRemainingBytesAsString();

  XML_Parser extParser = XML_ExternalEntityParserCreate(parser, param1.c_str(), param2.c_str());

  XML_ParserFree(parser);
  if (extParser) {
    XML_ParserFree(extParser);
  }

  return 0;
}