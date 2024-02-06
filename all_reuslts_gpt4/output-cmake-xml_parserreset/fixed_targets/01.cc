#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;  // out of memory, cannot proceed
  }

  std::string encoding = stream.ConsumeRandomLengthString();
  if (XML_ParserReset(parser, encoding.c_str()) == XML_FALSE) {
    XML_ParserFree(parser);
    return 0;
  }

  XML_ParserFree(parser);
  return 0;
}