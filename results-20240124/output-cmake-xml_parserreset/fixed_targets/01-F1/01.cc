#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <expat.h>

extern "C" {
#include "expat.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser)
    return 0;
  char *test_string = (char *)malloc(size + 1);
  memcpy(test_string, data, size);
  test_string[size] = 0;
  int result = XML_ParserReset(parser, test_string);
  free(test_string);
  XML_ParserFree(parser);
  return result;
}