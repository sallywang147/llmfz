 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libxml/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char* data_copy = (char*)malloc(size);
  if (!data_copy)
    return 0;
  memcpy(data_copy, data, size);

  char* namespace_sep = strchr(data_copy, '\n');
  if (!namespace_sep)
    return 0;
  *namespace_sep = '\0';
  namespace_sep++;

  XML_Parser parser = XML_ParserCreateNS(data_copy, *namespace_sep);
  if (!parser)
    return 0;

  XML_Parse(parser, data_copy, size, 1);
  XML_ParserFree(parser);

  free(data_copy);
  return 0;
}