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

  XML_Parser p = XML_ParserCreate(NULL);
  if (!p)
    return 0;

  XML_SetExternalEntityRefHandler(p, externalEntityInitProcessor2);

  int result = XML_Parse(p, test_file, size, true);
  XML_ParserFree(p);
  remove(test_file);
  return result;
}