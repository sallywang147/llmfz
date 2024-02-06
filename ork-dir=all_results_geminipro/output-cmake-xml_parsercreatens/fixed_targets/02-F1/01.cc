#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <expat.h>

extern "C" {
#include <libxml/parser.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* encoding = stream.ConsumeRemainingBytesAsString().c_str();
  XML_Parser parser = XML_ParserCreateNS(nullptr, 0);
  if (parser == nullptr) {
    return 0;
  }
  XML_SetEncoding(parser, encoding);
  XML_Parse(parser, nullptr, 0, XML_TRUE);
  XML_ParserFree(parser);
  return 0;
}