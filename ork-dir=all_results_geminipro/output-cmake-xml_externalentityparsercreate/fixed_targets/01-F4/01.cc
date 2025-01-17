#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"
#include "libxml/parserInternals.h"

extern "C" {
#include "libxml/xmlerror.h"
#include "libxml/xmlIO.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char test_file[] = "libfuzzer.xml";

  FILE *fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  XML_SetExternalEntityRefHandler(parser, XML_ExternalEntityParserCreate);

  XML_ParserFree(parser);
  remove(test_file);
  return 0;
}