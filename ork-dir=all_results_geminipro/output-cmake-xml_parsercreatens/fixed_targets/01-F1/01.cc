#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <libxml/parser.h>

extern "C" {
#include <libxml/parserInternals.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  XML_Parser parser = XML_ParserCreateNS(NULL, '\0');
  if (!parser) {
    return 0;
  }

  XML_Parse(parser, reinterpret_cast<const char*>(data), size, 1);
  XML_ParserFree(parser);

  return 0;
}