#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  XML_Parser parser = XML_ParserCreate(nullptr);
  if (!parser)
    return 0;

  char test_file[] = "libfuzzer.xml";

  FILE *fp = fopen(test_file, "wb");
  if (!fp) {
    XML_ParserFree(parser);
    return 0;
  }
  fwrite(data, size, 1, fp);
  fclose(fp);

  if (XML_ParseFile(parser, test_file) != XML_STATUS_OK) {
    XML_ParserFree(parser);
    remove(test_file);
    return 1;
  }

  if (XML_ParserReset(parser, test_file) != XML_STATUS_OK) {
    XML_ParserFree(parser);
    remove(test_file);
    return 1;
  }

  XML_ParserFree(parser);
  remove(test_file);
  return 0;
}