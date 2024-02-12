#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

extern "C" {
#include "libxml/parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_Parser parser = XML_ExternalEntityParserCreate(NULL, NULL, test_file);
  if (!parser) {
    return 1;
  }

  XML_Parse(parser, NULL, 0, 1);
  XML_ParserFree(parser);

  remove(test_file);
  return 0;
}