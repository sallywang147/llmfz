#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

extern "C" {
#include "libxml/parserInternals.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 1;
  }

  int ret = externalEntityInitProcessor2(parser, test_file, test_file, NULL);

  XML_ParserFree(parser);
  remove(test_file);
  return ret;
}