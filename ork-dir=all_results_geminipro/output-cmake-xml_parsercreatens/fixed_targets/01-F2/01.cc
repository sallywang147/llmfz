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

  XML_SetElementHandler(parser, start, end);
  XML_SetCharacterDataHandler(parser, char_data);
  XML_Parse(parser, reinterpret_cast<const char*>(data), size, 1);
  XML_ParserFree(parser);

  return 0;
}

extern "C" void start(void *ctx, const char *name, const char **atts) {
  printf("Start element: %s\n", name);
}

extern "C" void end(void *ctx, const char *name) {
  printf("End element: %s\n", name);
}

extern "C" void char_data(void *ctx, const char *ch, int len) {
  printf("Character data: %.*s\n", len, ch);
}