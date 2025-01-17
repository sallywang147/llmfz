 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  XML_Parser parser = XML_ParserCreate(nullptr);
  if (!parser)
    return 0;

  const char* const test_file = reinterpret_cast<const char* const>(data);

  XML_ParserReset(parser, test_file);

  XML_ParserFree(parser);
  return 0;
}