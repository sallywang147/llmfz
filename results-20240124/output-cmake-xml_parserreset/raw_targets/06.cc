 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser)
    return 0;

  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_ParserReset(parser, test_file);
  XML_ParserFree(parser);

  remove(test_file);
  return 0;
}