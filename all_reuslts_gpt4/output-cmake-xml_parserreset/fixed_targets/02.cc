#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a new parser
  XML_Parser parser = XML_ParserCreate(nullptr);
  if (!parser) {
    return 0;
  }

  // Get a random string for encoding
  std::string encoding = stream.ConsumeRandomLengthString();
  char* encoding_cstr = const_cast<char*>(encoding.c_str());

  // Reset the parser with the obtained encoding
  XML_ParserReset(parser, encoding_cstr);

  // Clean up
  XML_ParserFree(parser);

  return 0;
}