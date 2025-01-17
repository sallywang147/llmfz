 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_Parser parser = XML_ParserCreate(nullptr);
  if (!parser) {
    return 1;
  }

  XML_ExternalEntityParserCreate(parser, test_file, nullptr);

  XML_ParserFree(parser);
  remove(test_file);
  return 0;
}